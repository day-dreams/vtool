# vtool
video processing tool

我也不知道为什么要写cpp.

- 编译
    - `mkdir build;cd build; cmake ..;make`
- 运行
    - 剪切视频的第24帧图片
        - `ffmpegdemo cut YOUR_VIDEO_PATH 24`
        - 如果没有错误，生成文件在`./frame24.ppm`

