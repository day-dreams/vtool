#include <FfmpegRunnable.h>
#include "BaseRunnable.h"

int main() {

//    BaseRunnable r = BaseRunnable();
    BaseRunnable *r = new FfmpegRunnable();
    r->run();

    return 0;
}