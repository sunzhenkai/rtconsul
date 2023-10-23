#ifndef RTCFG_DEFINES_H
#define RTCFG_DEFINES_H

#include "string"
#include "unordered_map"
#include "list"
#include "vector"
#include "mutex"
#include "shared_mutex"

namespace rtcfg {
    typedef std::string String;
    template<typename K, typename V>
    using Map = std::unordered_map<K, V>;
    typedef Map<String, String> SSMap;
    typedef std::list<String> SList;
    using Mutex = std::mutex;
    using SMutex = std::shared_mutex;
    using Lock = std::lock_guard<Mutex>;
    using SLock = std::shared_lock<SMutex>;
    using ULock = std::shared_lock<SMutex>;
    typedef unsigned long int tid_t;
    template<typename T>
    using Vector = std::vector<T>;
}

#ifndef GET_OR_DEFAULT
#define GET_OR_DEFAULT(m, k, dft) m.find(k) != (m).end() ? (m).find(k)->second : dft
#endif // GET_OR_DEFAULT

#ifndef MOVE
#define MOVE(v) std::move(v)
#endif // MOVE

#endif //RTCFG_DEFINES_H
