#include "consul/client/consul_client.h"

namespace rtcfg::consul {
    String ConsulClient::GetKV(const String &key) {
        return http_client.Get(config.kv_url + key).content;
    }
}