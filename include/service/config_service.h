#ifndef RTCFG_CONFIG_SERVICE_H
#define RTCFG_CONFIG_SERVICE_H

#include "memory"
#include "defines.h"
#include "listener/listener.h"

namespace rtcfg {
    template<typename CacheValue>
    class ConfigService {
    public:
        virtual String Get(const String &key) = 0;
        virtual CacheValue Cache(const String &key) = 0;
        virtual void DiscardCache(const String &key) = 0;
        virtual void Subscribe(const String &key, Listener *listener) = 0;
        virtual void Unsubscribe(const String &key, Listener *listener) = 0;
        virtual ~ConfigService() = default;
    };

    template<typename CacheValue>
    using ConfigServicePtr = std::shared_ptr<ConfigService<CacheValue>>;
}


#endif //RTCFG_CONFIG_SERVICE_H
