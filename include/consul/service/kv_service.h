#ifndef RTCFG_KV_SERVICE_H
#define RTCFG_KV_SERVICE_H

#include "defines.h"
#include "listener/listener.h"
#include "service/config_service.h"
#include "consul/client/consul_client.h"

namespace rtcfg::consul {
    class ConsulKVService : public ConfigService {
    private:
        ConsulClient consul;
    public:
        explicit ConsulKVService(const SSMap &props) : consul(props) {
        }
        String Get(const String &key) override;
        String Cache(const String &key) override;
        void Subscribe(const String &key, Listener *listener) override;
    };
}

#endif //RTCFG_KV_SERVICE_H
