cmake_minimum_required(VERSION 3.14)
project(ffmpeg)

set(CMAKE_CXX_STANDARD 11)

add_executable(ffmpegdemo src/main.cpp src/BaseRunnable.cpp)
target_include_directories(ffmpegdemo PRIVATE include)





