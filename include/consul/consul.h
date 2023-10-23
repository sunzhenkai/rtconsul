#ifndef RTCFG_CONSUL_H
#define RTCFG_CONSUL_H

#include "consul/client/consul_client.h"
#include "consul/service/kv_service.h"
#include "consul/service/naming_service.h"

namespace rtcfg::consul {
    class Consul {
    private:
        ConsulClient consul_client_;
        ConsulKVService kv_service_;
        ConsulNamingService naming_service_;
    public:
        explicit Consul(const SSMap &props) : consul_client_(props), kv_service_(consul_client_),
                                              naming_service_(consul_client_) {}
        ConsulKVService &GetKVService();
        ConsulNamingService &GetNamingService();
    };
}

#endif //RTCFG_CONSUL_H
