#ifndef RTCFG_DEFINES_H
#define RTCFG_DEFINES_H

#include "string"
#include "unordered_map"
#include "list"
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
}

#ifndef GET_OR_DEFAULT
#define GET_OR_DEFAULT(m, k, dft) m.find(k) != (m).end() ? (m).find(k)->second : dft
#endif //GET_OR_DEFAULT

#endif //RTCFG_DEFINES_H
