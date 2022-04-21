#include "consul/client/consul_client.h"

namespace rtcfg::consul {
    std::pair<long, String> ConsulClient::GetKV(const String &path, const SSMap &params) {
        auto &kv_url = config.kv_url;
        assert(!kv_url.empty());
        String url = kv_url[kv_url.length() - 1] == '/' ? kv_url + path : kv_url + "/" + path;
        auto rsp = http_client.Get(url, params);
        auto it = rsp.headers.find(KEY_CONSUL_INDEX);
        assert(it != rsp.headers.end());
        return std::make_pair(std::stol(it->second), rsp.content);
    }
}