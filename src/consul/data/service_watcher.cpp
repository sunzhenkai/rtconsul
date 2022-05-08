#include "consul/data/service_watcher.h"

namespace rtcfg::consul {
    void ConsulServiceWatcher::DoWatch() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        spdlog::debug("do watch");
    }
}