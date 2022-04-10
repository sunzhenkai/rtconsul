#ifndef RTCFG_CONFIG_SERVICE_H
#define RTCFG_CONFIG_SERVICE_H

#include "memory"
#include "defines.h"
#include "listener/listener.h"

namespace rtcfg {
    class ConfigService {
    public:
        virtual String Get(const String &key) = 0;
        virtual String Cache(const String &key) = 0;
        virtual void Subscribe(const String &key, Listener *listener) = 0;
        virtual ~ConfigService() = default;
    };

    typedef std::shared_ptr<ConfigService> ConfigServicePtr;
}


#endif //RTCFG_CONFIG_SERVICE_H
