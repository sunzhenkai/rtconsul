#ifndef RTCFG_UTILS_H
#define RTCFG_UTILS_H

#include "defines.h"

namespace rtcfg {
    template<typename K, typename V>
    static V &GetOrDefault(Map<K, V> &m, K &key, V &dft) {
        auto it = m.find(key);
        return it == m.end() ? dft : it->second;
    }

    static bool EndWith(const String &v, const char &c) {
        if (v.empty()) {
            return false;
        } else {
            return v[v.length() - 1] == c;
        }
    }
}


#endif //RTCFG_UTILS_H
