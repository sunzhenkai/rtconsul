#include "iostream"
#include "thread/thread.h"
#include "spdlog/spdlog.h"

void fn(void *data) {

}

int main() {
    auto f = [](void *data) {

    };
    rtcfg::Thread t("test_thread", fn);
    return 0;
}