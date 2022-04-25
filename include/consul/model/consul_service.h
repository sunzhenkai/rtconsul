#ifndef RTCFG_SERVICE_INSTANCE_H
#define RTCFG_SERVICE_INSTANCE_H

#include "defines.h"

namespace rtcfg::consul {
    struct Address {
        String address;
        int port;
    };

    struct TaggedAddresses {
        Address lan;
        Address wan;
    };

    struct Meta {
        SSMap data;
    };

    struct Node {
        String id;
        String node;
        String address;
        String data_center;
        TaggedAddresses tagged_addresses;
        Meta meta;
        int64_t create_index;
        int64_t modify_index;
    };

    struct ServiceWeights {
        int passing;
        int warning;
    };

    struct Service {
        String id;
        String service;
        Vector<String> tags;
        String address;
        Meta meta;
        int port;
        bool enable_tag_override;
        TaggedAddresses tagged_addresses;
        int64_t create_index;
        int64_t modify_index;
        String name_space;
    };

    struct Check {
        String node;
        String check_id;
        String name;
        String status;
        String notes;
        String output;
        String service_id;
        String service_name;
        Vector<String> service_tags;
        String name_space;
    };

    struct PassingServices {
        Node node;
        Service service;
        Vector<Check> checks;
    };

    typedef std::shared_ptr<PassingServices> PassingServicesPtr;
}

#endif //RTCFG_SERVICE_INSTANCE_H
