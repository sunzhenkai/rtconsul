#ifndef RTCFG_CONSUL_CLIENT_H
#define RTCFG_CONSUL_CLIENT_H

#include "spdlog/spdlog.h"
#include "defines.h"
#include "constants/constants.h"
#include "http/http_client.h"
#include "utils/utils.h"

namespace rtcfg::consul {
    struct ConsulConfig {
        String host;
        String kv_url;
        String health_service_url;
    };

    class ConsulClient {
    private:
        ConsulConfig config;
        HTTPClient http_client;
    public:
        explicit ConsulClient(const SSMap &props) {
            config = ConsulConfig{
                    GET_OR_DEFAULT(props, KEY_HOST, CONSUL_DEFAULT_URL),
                    GET_OR_DEFAULT(props, KEY_HOST, CONSUL_DEFAULT_URL) + CONSUL_KV_PREFIX,
                    GET_OR_DEFAULT(props, KEY_HOST, CONSUL_DEFAULT_URL) + CONSUL_HEALTH_SERVICE
            };
        }

        std::pair<long, String> GetKV(const String &path, const SSMap &params = EMPTY_SS_MAP);
        std::pair<long, String> GetHealthService(const String &service, const SSMap &params = EMPTY_SS_MAP);
    };
}

#endif //RTCFG_CONSUL_CLIENT_H
