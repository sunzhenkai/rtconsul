#include "consul/data/service_watcher.h"

namespace rtcfg::consul {
    void ConsulServiceWatcher::DoWatch() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        SSMap params{{"index", std::to_string(data_index_)}};
        auto rsp = consul_.GetHealthService(service_, params);
        spdlog::debug("[ConsulServiceWatcher::DoWatch] response. {index={}, response={}}",
                      rsp.first, rsp.second);
        data_index_ = rsp.first;
    }
}