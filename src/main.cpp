#include <FfmpegRunnable.h>
#include "BaseRunnable.h"
#include "ScreenShot.h"
#include "Utils.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include<map>
#include<functional>

int main(int argc, char **argv) {
    info("cmd starting ......");

    BaseRunnable *r = nullptr;
    std::map<string, std::function<void()>> handlers = {};
    handlers["cut"] = [&] {
        r = new ScreenShot(argv[2], argv[3]);
    };

    auto handler = handlers.find(argv[1]);
    if (handler != handlers.end()) {
        handler->second();
        r->run();
    }
    return 0;
}