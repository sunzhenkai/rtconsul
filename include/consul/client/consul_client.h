#ifndef RTCFG_CONSUL_CLIENT_H
#define RTCFG_CONSUL_CLIENT_H

#include "defines.h"
#include "constants/constants.h"

namespace rtcfg::consul {
    struct ConsulConfig {
        String host;
    };

    class ConsulClient {
    private:
        ConsulConfig config;
    public:
        explicit ConsulClient(const SSMap &props) {
            config = ConsulConfig{props.find(KEY_HOST)->second};
        }
    };
}

#endif //RTCFG_CONSUL_CLIENT_H
