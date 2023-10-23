#include "consul/data/service_watcher.h"
#include "iostream"
#include "exceptions.h"

namespace rtcfg::consul {
    void ConsulServiceWatcher::DoWatch() {
        static std::string LOG = "[ConsulServiceWatcher::DoWatch]";
        spdlog::debug("service watcher: do watch");
        SSMap params{{"index", std::to_string(data_index_)}};
        try {
            auto rsp = consul_.GetHealthService(service_, params);
            spdlog::debug("{} response. [index={}, response={}]", LOG, rsp.first, rsp.second);
            auto j = nlohmann::json::parse(rsp.second);
            ServiceInstances services(j);
            // TODO save services
            data_index_ = rsp.first;
        } catch (const ReadTimeoutException &e) {
            spdlog::debug("{} timeout. [e={}]", LOG, e.what());
        } catch (const std::exception &e) {
            spdlog::error("{} unexpected error. [e={}]", LOG, e.what());
        }
    }
}