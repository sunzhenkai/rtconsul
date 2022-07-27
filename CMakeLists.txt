project(rtcfg)
cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_STANDARD 17)

include_directories(include)

include(external/utils.cmake)
include(external/spdlog/check.cmake)
include(external/openssl/check.cmake)
include(external/curl/check.cmake)
include(external/json/check.cmake)

aux_source_directory(src SRCS_DIRS)
aux_source_directory(src/constants SRCS_DIRS)
aux_source_directory(src/factory SRCS_DIRS)
aux_source_directory(src/model SRCS_DIRS)
aux_source_directory(src/service SRCS_DIRS)
aux_source_directory(src/http SRCS_DIRS)
aux_source_directory(src/utils SRCS_DIRS)
aux_source_directory(src/consul SRCS_DIRS)
aux_source_directory(src/consul/client SRCS_DIRS)
aux_source_directory(src/consul/data SRCS_DIRS)
aux_source_directory(src/consul/service SRCS_DIRS)
aux_source_directory(src/thread SRCS_DIRS)

set(EXTRA spdlog::spdlog
        nlohmann_json::nlohmann_json
        curl::curl
        openssl::ssl
        openssl::crypto
        pthread
        z
        dl
        m)

add_library(rtcfg-static STATIC ${SRCS_DIRS})
target_link_libraries(rtcfg-static PRIVATE ${EXTRA})
install(TARGETS rtcfg-static LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include/rtcfg
        FILES_MATCHING PATTERN "*.h*")

option(BUILD_TEST "build tests" OFF)
if (BUILD_TEST)
    include(cmakes/sample.cmake)
    include(cmakes/test.cmake)
endif ()