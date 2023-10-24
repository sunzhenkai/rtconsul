PROJECT(rtcfg)
CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
SET(CMAKE_CXX_STANDARD 17)
OPTION(BUILD_TEST "build tests" OFF)

INCLUDE_DIRECTORIES(include)

#include(external/spdlog/check.cmake)
#include(external/openssl/check.cmake)
#include(external/curl/check.cmake)
#include(external/json/check.cmake)

AUX_SOURCE_DIRECTORY(src SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/constants SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/factory SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/model SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/service SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/http SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/utils SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/consul SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/consul/client SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/consul/data SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/consul/service SRCS_DIRS)
AUX_SOURCE_DIRECTORY(src/thread SRCS_DIRS)

SET(EXTRA
#        spdlog::spdlog
#        nlohmann_json::nlohmann_json
#        curl::curl
#        openssl::ssl
#        openssl::crypto
        pthread
        z
        dl
        m)

ADD_LIBRARY(rtcfg-static STATIC ${SRCS_DIRS})
TARGET_LINK_LIBRARIES(rtcfg-static PRIVATE ${EXTRA})
INSTALL(TARGETS rtcfg-static LIBRARY DESTINATION lib)
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include/rtcfg
        FILES_MATCHING PATTERN "*.h*")

IF (BUILD_TEST)
    INCLUDE(external/googletest/check.cmake)
    INCLUDE(cmakes/sample.cmake)
    INCLUDE(cmakes/test.cmake)
    INCLUDE(cmakes/gtest.cmake)
ENDIF ()