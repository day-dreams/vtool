//
// Created by day-dreams on 2020-03-26.
//

#ifndef FFMPEG_UTILS_H
#define FFMPEG_UTILS_H

#include <string>
#include <spdlog/spdlog.h>

using std::string;

template<typename... Args>
inline void error(spdlog::string_view_t fmt, const Args &... args) {
    spdlog::error(fmt, args...);
}

template<typename... Args>
inline void info(spdlog::string_view_t fmt, const Args &... args) {
    spdlog::info(fmt, args...);
}

template<typename... Args>
inline void panic(spdlog::string_view_t fmt, const Args &... args) {
    spdlog::error(fmt, args...);
    exit(-1);
}

template<class T>
inline T must(T t) {
    if (t == nullptr) {
        spdlog::error("nil ptr");
        exit(-1);
    }
    return t;
}

template<>
inline int must(int t) {
    if (t < 0) {
        spdlog::error("rcode(%d) < 0.", t);
        exit(-1);
    }
    return t;
}

template<class T>
inline void arrayMustHaveElementsMoreThan(T *t, int len) {
    if (sizeof(t) <= len) {
        panic("array must have more elements than {}", len);
    }
}


#endif //FFMPEG_UTILS_H
