#if !defined(SCREEN_SHOT_H)
#define SCREEN_SHOT_H

#include "BaseRunnable.h"
#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
}

using std::string;

class ScreenShot : public BaseRunnable {
private:
    string path; //视频文件地址
    string output;//输出文件
    int at;      //第几帧
public:

    ScreenShot(string videoPath, string at);

    void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame);

    void run();
};

#endif // SCREEN_SHOT_H
