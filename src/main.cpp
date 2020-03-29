#include "BaseRunnable.h"
#include "ScreenShot.h"
#include "Hello.h"
#include <map>
#include <functional>
#include <gflags/gflags.h>

DEFINE_string(cmd, "", "vtool cmd");
DEFINE_string(video, "", "[cut] path of video file");
DEFINE_string(frame, "", "[cut] frame number");

int main(int argc, char **argv) {

    gflags::SetUsageMessage(
            "vtool [cmd] [params...] \n"
            "usage:\n"
            "\t- save one frame from video to local file\n"
            "\t\tvtool --cmd=cut --video=${video file path} --frame=${frame number}\n"
    );
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    BaseRunnable *r = nullptr;
    std::map<string, std::function<void()>> handlers = {
            {"cut", [&] { r = new ScreenShot(FLAGS_video, FLAGS_frame); }}
    };

    auto handler = handlers.find(FLAGS_cmd);
    if (handler != handlers.end()) {
        handler->second();
        r->Run();
    }
    return 0;
}