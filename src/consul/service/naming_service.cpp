#include "consul/service/naming_service.h"

namespace rtcfg::consul {
    String ConsulNamingService::Get(const String &service, const SSMap &params) {
        return consul_client_.GetHealthService(service, params).second;
    }

    ConsulServiceWatcherPtr ConsulNamingService::Cache(const String &service) {
        auto result = std::shared_ptr<ConsulServiceWatcher>(nullptr);
        if (!caches.Find(service, result)) {
            result = std::make_shared<ConsulServiceWatcher>(consul_client_, service);
            caches.Insert(service, result);
        }
        return result;
    }
}