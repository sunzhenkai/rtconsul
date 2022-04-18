#ifndef RTCFG_CONSUL_KV_H
#define RTCFG_CONSUL_KV_H

#include "defines.h"
#include "utils/safe_map.h"
#include <vector>
#include "nlohmann/json.hpp"

namespace rtcfg::consul {
    class ConsulKV {
    public:
        long lock_index{};
        String key;
        int flags{};
        String value;
        long create_index{};
        long modify_index{};

        ConsulKV() = default;
        ConsulKV(const ConsulKV &) = default;
        explicit ConsulKV(nlohmann::json &j) {
            lock_index = j["LockIndex"].get<long>();
            key = j["Key"].get<std::string>();
            flags = j["Flags"].get<int>();
            value = j["Value"].get<std::string>();
            create_index = j["CreateIndex"].get<long>();
            modify_index = j["ModifyIndex"].get<long>();
        }
    };

    using ConsulKVGroup = Map<String, ConsulKV>;
    using ConsulKVVector = std::vector<ConsulKV>;
}


#endif //RTCFG_CONSUL_KV_H
