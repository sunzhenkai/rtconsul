#include "consul/consul.h"

namespace rtcfg::consul {
    ConsulKVService &Consul::GetKVService() {
        return kv_service_;
    }

    ConsulNamingService &Consul::GetNamingService() {
        return naming_service_;
    }
}