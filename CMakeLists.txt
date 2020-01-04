cmake_minimum_required(VERSION 3.14)
project(ffmpeg)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-D__STDC_CONSTANT_MACROS")
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(ffmpegdemo src/main.cpp src/BaseRunnable.cpp src/FfmpegRunnable.cpp include/FfmpegRunnable.h)
target_include_directories(ffmpegdemo PRIVATE include)
target_link_libraries(ffmpegdemo PRIVATE avformat avutil)





