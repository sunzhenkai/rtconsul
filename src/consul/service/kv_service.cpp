#include "consul/service/kv_service.h"

namespace rtcfg::consul {
    String ConsulKVService::Get(const String &key) {
        return "hello";
    }

    String ConsulKVService::Cache(const String &key) {
        return "hi";
    }

    void ConsulKVService::Subscribe(const String &key, Listener *listener) {

    }
}