#include "consul/service/kv_service.h"

namespace rtcfg::consul {
    String ConsulKVService::Get(const String &key, const SSMap &params) {
        return consul_client_.GetKV(key, params).second;
    }

    ConsulKVWatcherPtr ConsulKVService::Cache(const String &key) {
        auto result = std::shared_ptr<ConsulKVWatcher>(nullptr);
        if (!caches.Find(key, result)) {
            result = std::make_shared<ConsulKVWatcher>(consul_client_, key);
            caches.InsertIfAbsent(key, result);
        }
        result->Start();
        return result;
    }

    void ConsulKVService::DiscardCache(const String &key) {}

    void ConsulKVService::Subscribe(const String &key, Listener *listener) {}

    void ConsulKVService::Unsubscribe(const String &key, Listener *listener) {}
}