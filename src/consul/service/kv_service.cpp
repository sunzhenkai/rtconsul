#include "consul/service/kv_service.h"
#include "nlohmann/json.hpp"

namespace rtcfg::consul {
    String ConsulKVService::Get(const String &key) {
        return consul.GetKV(key);
    }

    ConsulKVWatcherPtr ConsulKVService::Cache(const String &key) {
        auto result = std::shared_ptr<ConsulKVWatcher>(nullptr);
        if (!caches.Find(key, result)) {
            result = std::make_shared<ConsulKVWatcher>(key, [&]() -> ConsulKVGroup {
                auto result = ConsulKVGroup{};
                auto rsp = consul.GetKV(key);
                auto j = nlohmann::json::parse(rsp);
                for (auto &e: j) {
                    result[key] = ConsulKV(e);
                }
                return std::move(result);
            });
            caches.Insert(key, result);
        }
        return result;
    }

    void ConsulKVService::DiscardCache(const String &key) {}

    void ConsulKVService::Subscribe(const String &key, Listener *listener) {
    }

    void ConsulKVService::Unsubscribe(const String &key, Listener *listener) {
    }
}