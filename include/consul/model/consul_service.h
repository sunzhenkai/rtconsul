#ifndef RTCFG_SERVICE_INSTANCE_H
#define RTCFG_SERVICE_INSTANCE_H

#include <cassert>
#include "defines.h"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

namespace rtcfg::consul {
#define SET_JSON_STR_NON_EMPTY(f, v, j) if (v.size() != 0) j[f] = v

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

        nlohmann::json ToJson() {
            return nlohmann::json{data};
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

    struct CheckBasic {
        String id;
        String name;
    };

    struct TCPAndHTTPCheckBasic {
        String interval;
        String timeout;
    };

    struct HTTPCheck : CheckBasic, TCPAndHTTPCheckBasic {
        String http;
        String method;
    };

    struct TCPCheck : CheckBasic, TCPAndHTTPCheckBasic {
        String tcp;
    };

    struct TTLCheck : CheckBasic {
        String ttl;
    };

    // check define https://www.consul.io/docs/discovery/checks
    struct Check : HTTPCheck, TCPCheck, TTLCheck {
        nlohmann::json ToJson() {
            auto result = nlohmann::json{};
//            SET_JSON_STR_NON_EMPTY("id", id, result);
        }
    };

    struct Checks {
        std::vector<Check> checks;

        nlohmann::json ToJson() {
            return nlohmann::json::parse(checks);
        }
    };

    // service define https://www.consul.io/docs/discovery/services
    struct Service {
        String name;
        String id;
        int port;
        std::vector<String> tags;
        Meta meta;
        TaggedAddresses taggedAddresses;
        Checks checks;

        nlohmann::json ToJson() {
            return nlohmann::json{
                    {"name",   name},
                    {"id",     id},
                    {"port",   port},
                    {"tags",   tags},
                    {"meta",   meta.ToJson()},
                    {"checks", checks.ToJson()}
            };
        }
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
