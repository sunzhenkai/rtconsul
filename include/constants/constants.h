#pragma once

#include "defines.h"

namespace rtcfg {
    extern const String KEY_PROTOCOL;
    extern const String KEY_HOST;
    extern const String KEY_CONSUL;
    extern const String KEY_CONSUL_INDEX;

    extern const String CONSUL_DEFAULT_URL;
    extern const String CONSUL_KV_PREFIX;
    extern const String CONSUL_HEALTH_SERVICE;

    extern const SSMap EMPTY_SS_MAP; // read prefix value
    extern const SSMap CONSUL_KV_KEYS; // read keys
    extern const SSMap CONSUL_KV_RECURSE; // read value recursive
}

