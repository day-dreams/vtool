//
// Created by day-dreams on 2020-03-27.
//

#ifndef FFMPEG_DEFER_H
#define FFMPEG_DEFER_H

#include <functional>

//  go/defer的仿造
class Defer {
public:
    Defer(std::function<void()> &&f) : func_(f) {}

    ~Defer() {
        if (func_ != nullptr) {
            func_();
        }
    }

    Defer(const Defer &) = delete;

    Defer(Defer &&) = delete;

    void operator=(const Defer &) = delete;

private:
    std::function<void()> func_;
};

#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#define defer(expr) Defer CONCAT(_d_, __COUNTER__)\
(std::move(std::function<void()>([&](){expr;})))

#endif //FFMPEG_DEFER_H
