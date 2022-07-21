#ifndef RTCFG_SAFE_MAP_H
#define RTCFG_SAFE_MAP_H

#include "defines.h"

namespace rtcfg {
    template<typename K, typename V>
    class SafeMap {
        SMutex mtx;
        Map <K, V> data;
    public:
        SafeMap() = default;
        SafeMap(SafeMap &) = default;

        void Insert(const K &k, const V &v) {
            ULock lock(mtx);
            data.insert({k, v});
        }

        void InsertIfAbsent(const K &k, const V&v) {
            ULock lock(mtx);
            if (data.find(k) == data.end()) {
                data.insert({k, v});
            }
        }

        bool Find(const K &k, V &result) {
            SLock lock(mtx);
            auto it = data.find(k);
            if (it != data.end()) {
                result = it->second;
                return true;
            }
            return false;
        }

        size_t Erase(const K &k) {
            ULock lock(mtx);
            return data.erase(k);
        }

        size_t Size() {
            return data.size();
        }
    };
}

#endif //RTCFG_SAFE_MAP_H
