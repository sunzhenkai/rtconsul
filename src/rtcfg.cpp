#include "rtcfg.h"
#include "constants/constants.h"
#include "exceptions.h"
#include "consul/service/kv_service.h"

namespace rtcfg {
    ConfigServicePtr RTCFG::GetConfigService(const SSMap &config) {
        auto it = config.find(KEY_PROTOCOL);
        if (it == config.end()) {
            throw RTException("protocol not set");
        }

        if (it->second.rfind(KEY_CONSUL, 0) == 0) {
            return std::make_shared<consul::ConsulKVService>(config);
        } else {
            throw RTException("unsupported protocol");
        }
    }
}