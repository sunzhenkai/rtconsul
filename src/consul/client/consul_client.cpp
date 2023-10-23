#include "consul/client/consul_client.h"

namespace rtcfg::consul {
    std::pair<long, String> ConsulClient::GetKV(const String &path, const SSMap &params) {
        auto &kv_url = config.kv_url;
        assert(!kv_url.empty());
        String url = EndWith(kv_url, '/') ? kv_url + path : kv_url + '/' + path;
        auto rsp = http_client.Get(url, params);
        auto it = rsp.headers.find(KEY_CONSUL_INDEX);
        assert(it != rsp.headers.end());
        return std::make_pair(std::stol(it->second), rsp.content);
    }

    std::pair<long, String> ConsulClient::GetHealthService(const String &service, const SSMap &params) {
        auto &base_url = config.health_service_url;
        assert(!base_url.empty());
        String url = EndWith(base_url, '/') ? base_url + service : base_url + '/' + service;
        auto rsp = http_client.Get(url, params);
//        spdlog::debug("[ConsulClient::GetHealthService] http raw response. [url={} service={}, response={}]",
//                      url, service, rsp.content);
        auto it = rsp.headers.find(KEY_CONSUL_INDEX);
        assert(it != rsp.headers.end());
        return std::make_pair(std::stol(it->second), rsp.content);
    }
}