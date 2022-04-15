#ifndef RTCFG_DEFINES_H
#define RTCFG_DEFINES_H

#include "string"
#include "unordered_map"
#include "list"

namespace rtcfg {
    typedef std::string String;
    template<typename K, typename V>
    using Map = std::unordered_map<K, V>;
    typedef Map<String, String> SSMap;
    typedef std::list<String> SList;
}

#ifndef GET_OR_DEFAULT
#define GET_OR_DEFAULT(m, k, dft) m.find(k) != (m).end() ? (m).find(k)->second : dft
#endif //GET_OR_DEFAULT

#endif //RTCFG_DEFINES_H
