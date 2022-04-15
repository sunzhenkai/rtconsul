#include "consul/service/kv_service.h"

namespace rtcfg::consul {
    String ConsulKVService::Get(const String &key) {
        return consul.GetKV(key);
    }

    String ConsulKVService::Cache(const String &key) {
        return "hi";
    }

    void ConsulKVService::Subscribe(const String &key, Listener *listener) {
    }
}