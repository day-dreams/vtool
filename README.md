# vtool
video processing tool

我也不知道为什么要写cpp.

- 依赖
    - ubuntu, `sudo apt-get install libgflags-dev ffmpeg libmp3lame0`
    - macos, `brew install gflags ffmpeg`
- 编译
    - `mkdir build;cd build; cmake ..;make`
- 运行
    - 剪切视频的第24帧图片保存到文件
        - `./vtool --cmd=cut --video=/Users/kakaxi/Desktop/huojianshaonv101.MP4 --frame=24`