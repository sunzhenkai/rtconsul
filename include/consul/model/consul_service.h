#ifndef RTCFG_SERVICE_INSTANCE_H
#define RTCFG_SERVICE_INSTANCE_H

#include <cassert>
#include "defines.h"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

namespace rtcfg::consul {
    struct Address {
        String address;

        explicit Address(const nlohmann::json &j) {
            if (j.is_string()) {
                address = j.get<String>();
            } else if (j.contains("address")) {
                address = j["address"].get<String>();
            }
        }
    };

    struct TaggedAddresses {
        Address lan;
        Address wan;

        explicit TaggedAddresses(const nlohmann::json &j) :
                lan(j["lan"].get<nlohmann::json>()),
                wan(j["wan"].get<nlohmann::json>()) {}
    };

    struct Meta {
        SSMap data;

        explicit Meta(const nlohmann::json &j) {
            for (auto &[k, v]: j.items()) {
                data[k] = v;
            }
        }
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

        explicit Node(const nlohmann::json &j) :
                id(j["ID"].get<String>()),
                node(j["Node"].get<String>()),
                address(j["Address"].get<String>()),
                data_center(j["Datacenter"].get<String>()),
                tagged_addresses(j["TaggedAddresses"].get<nlohmann::json>()),
                meta(j["Meta"].get<nlohmann::json>()),
                create_index(j["CreateIndex"].get<int64_t>()),
                modify_index(j["ModifyIndex"].get<int64_t>()) {}
    };

    struct Tags {
        Vector<String> tags;

        explicit Tags(const nlohmann::json &j) {
            assert(j.is_array());
            tags.reserve(j.size());
            for (auto &e: j) {
                tags.emplace_back(e.get<String>());
            }
        }
    };

    struct Weights {
        int passing;
        int warning;

        explicit Weights(const nlohmann::json &j) :
                passing(j["Passing"].get<int>()),
                warning(j["Warning"].get<int>()) {}
    };

    // check define https://www.consul.io/docs/discovery/checks
    struct Check {
        // common
        String id;
        String name;
        // http & tcp
        String interval;
        String timeout;
        // http check
        String http;
        String method;
        // tcp
        String tcp;
        // ttl check
        String ttl;
    };

    struct Checks {
        std::vector<Check> checks;
    };

    // service define https://www.consul.io/docs/discovery/services
    struct Service {

    };

    struct RService {
        String id;
        String service;
        Tags tags;
        String address;
        Meta meta;
        int port;
        bool enable_tag_override;
        int64_t create_index;
        int64_t modify_index;
        String name_space;

        explicit RService(const nlohmann::json &j) :
                id(j["ID"].get<String>()),
                service(j["RService"].get<String>()),
                address(j["Address"].get<String>()),
                meta(j["Meta"].get<nlohmann::json>()),
                port(j["Port"].get<int>()),
                enable_tag_override(j["EnableTagOverride"].get<bool>()),
                create_index(j["CreateIndex"].get<int64_t>()),
                modify_index(j["ModifyIndex"].get<int64_t>()),
                tags(j["Tags"].get<nlohmann::json>()) {}
    };

    struct ServiceInstance {
        Node node;
        RService service;

        explicit ServiceInstance(const nlohmann::json &j) :
                node(j["Node"].get<nlohmann::json>()),
                service(j["RService"].get<nlohmann::json>()) {}
    };

    struct ServiceInstances {
        Vector<ServiceInstance> instances;

        explicit ServiceInstances(const nlohmann::json &j) {
            assert(j.is_array());
            for (auto &e: j) {
                spdlog::debug("{}", e.dump(4));
                instances.emplace_back(e);
            }
        }
    };

    typedef std::shared_ptr<ServiceInstances> ServiceInstancesPtr;
}

#endif //RTCFG_SERVICE_INSTANCE_H
