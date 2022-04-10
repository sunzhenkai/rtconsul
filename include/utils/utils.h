#ifndef RTCFG_UTILS_H
#define RTCFG_UTILS_H

#include "unordered_map"

namespace rtcfg {
    template<typename K, typename V>
    static V &GetOrDefault(std::unordered_map<K, V> &m, K &key, V &dft) {
        auto it = m.find(key);
        return it == m.end() ? dft : it->second;
    }
}


#endif //RTCFG_UTILS_H
