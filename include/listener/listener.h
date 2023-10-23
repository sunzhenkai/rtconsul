#ifndef RTCFG_LISTENER_H
#define RTCFG_LISTENER_H

#include "defines.h"

namespace rtcfg {
    class Listener {
    public:
        virtual void OnChange(const String &data) = 0;
    };
}

#endif //RTCFG_LISTENER_H
