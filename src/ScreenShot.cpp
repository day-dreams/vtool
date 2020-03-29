#include "ScreenShot.h"
#include "Utils.h"
#include "Defer.h"
#include <string>
#include <functional>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

void ScreenShot::Run() {
    av_register_all();
    // get video header info
    AVFormatContext *pFormatCtx = nullptr;
    if (avformat_open_input(&pFormatCtx, this->path.c_str(), nullptr, nullptr) != 0) {
        panic("open av file failed");
    }
    // get stream info
    if (avformat_find_stream_info(pFormatCtx, nullptr) < 0) {
        panic("find stream info failed");
    }

    // print format info
    av_dump_format(pFormatCtx, 0, this->path.c_str(), 0);

    // get video stream
    auto vStream = -1;
    for (int i = 0; i < pFormatCtx->nb_streams; ++i) {
        auto stream = pFormatCtx->streams[i];
        if (stream->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            vStream = i;
            break;
        }
    }
    if (vStream == -1) {
        panic("fail to find video stream");
    }

    // get codec ctx
    auto pCodecCtx = pFormatCtx->streams[vStream]->codec;
    // get decoder
    auto pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == nullptr) {
        panic("unknown codec type. %d", pCodecCtx->codec_id);
    }
    // open codec/decoder
    AVDictionary *optDict = NULL;
    if (avcodec_open2(pCodecCtx, pCodec, &optDict) < 0) {
        panic("fail to open decoder");
    }
    // allocate memory for one frame
    auto pframe = must(av_frame_alloc());
    auto pframergb = must(av_frame_alloc());
    defer(
            av_frame_free(&pframe);
            av_frame_free(&pframergb);
    );
    auto numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
    auto buffer = must((uint8_t *) av_malloc(numBytes * sizeof(uint8_t)));
    defer (
            av_free(buffer);
    );


    auto sws_ctx = sws_getContext(
            pCodecCtx->width,
            pCodecCtx->height,
            pCodecCtx->pix_fmt,
            pCodecCtx->width,
            pCodecCtx->height,
            AV_PIX_FMT_RGB24,
            SWS_BILINEAR,
            NULL,
            NULL,
            NULL
    );

    must(avpicture_fill((AVPicture *) pframergb, buffer, AV_PIX_FMT_RGB24,
                        pCodecCtx->width, pCodecCtx->height));

    AVPacket packet;
    int frameFinished = 0, index = 0;
    while (true) {//read one frame
        auto ret = av_read_frame(pFormatCtx, &packet);
        if (ret < 0) {
            break;
        }

        // check whether is video stream
        if (packet.stream_index == vStream) {
            // decode
            must(avcodec_decode_video2(pCodecCtx, pframe, &frameFinished, &packet));

            if (frameFinished) {
                ++index;
                if (index == this->at) {
                    sws_scale(
                            sws_ctx,
                            (uint8_t const *const *) pframe->data,
                            pframe->linesize,
                            0,
                            pCodecCtx->height,
                            pframergb->data,
                            pframergb->linesize
                    );
                    this->SaveFrame(pframergb, pCodecCtx->width, pCodecCtx->height, this->at);
                    break;
                }
            }
        }
    }
    if (index != this->at) {
        error("frame not enough. want {0}, but total {1}", this->at, index);
    }
    avformat_close_input(&pFormatCtx);
}

ScreenShot::ScreenShot(string videoPath, string at) {
    this->path = videoPath;
    this->output = "./output";
    auto val = std::stoi(at);
    if (val <= 0) {
        panic("wrong param");
    }
    this->at = val;
}

void ScreenShot::SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
    FILE *pFile;
    char szFilename[32];
    int y;

    // Open file
    sprintf(szFilename, "frame%d.ppm", iFrame);
    pFile = fopen(szFilename, "wb");
    if (pFile == NULL)
        return;

    // Write header
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);

    // Write pixel data
    for (y = 0; y < height; y++)
        fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, width * 3, pFile);

    // Close file
    fclose(pFile);

    info("frame had been write to frame{}.ppm", iFrame);
}
