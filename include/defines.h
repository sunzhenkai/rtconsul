#ifndef RTCFG_DEFINES_H
#define RTCFG_DEFINES_H

#include "string"
#include "map"
#include "list"

namespace rtcfg {
    typedef std::string String;
    typedef std::map<String, String> SSMap;
    typedef std::list<String> SList;
}

#ifndef GET_OR_DEFAULT
#define GET_OR_DEFAULT(dest, m, key, dft) auto it = (m).find(key); (dest) = it == (m).end() ? (dft) : it->second
#endif //GET_OR_DEFAULT

#endif //RTCFG_DEFINES_H
