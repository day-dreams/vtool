//
// Created by day-dreams on 2020-01-04.
//

#include "../include/FfmpegRunnable.h"
#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/dict.h>
}

using namespace std;


void printMetaData(string path) {
    AVFormatContext *fmt_ctx = NULL;
    AVDictionaryEntry *tag = NULL;
    int ok = 0;
    if ((ok = avformat_open_input(&fmt_ctx, &path[0], nullptr, nullptr)) != 0) {
        av_log(nullptr, AV_LOG_ERROR, "Open av file failed\n");
        return;
    }

    if ((ok = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot find stream information\n");
        return;
    }

    while ((tag = av_dict_get(fmt_ctx->metadata, "", tag, AV_DICT_IGNORE_SUFFIX)))
        printf("av info\t%s=%s\n", tag->key, tag->value);

    avformat_close_input(&fmt_ctx);

}

void FfmpegRunnable::run() {
    string path = "/Users/kakaxi/Desktop/huojianshaonv101.MP4";
    printMetaData(path);
}