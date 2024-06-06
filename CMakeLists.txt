CMAKE_MINIMUM_REQUIRED(VERSION 3.24)
SET(CMAKE_CXX_STANDARD 17)
PROJECT(rtcfg)
OPTION(BUILD_TEST "build tests" OFF)

INCLUDE_DIRECTORIES(include)

FIND_PACKAGE(OpenSSL REQUIRED)
FIND_PACKAGE(CURL CONFIG REQUIRED)
FIND_PACKAGE(nlohmann_json CONFIG REQUIRED)
FIND_PACKAGE(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE SRCS src/**.cpp)

SET(LIB_DEPS OpenSSL::SSL
        OpenSSL::Crypto
        CURL::libcurl
        nlohmann_json::nlohmann_json
        spdlog::spdlog
)

ADD_LIBRARY(rtcfg ${SRCS})
TARGET_LINK_LIBRARIES(rtcfg PRIVATE ${LIB_DEPS})

# install
INSTALL(TARGETS rtcfg LIBRARY DESTINATION lib)
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include/rtcfg
        FILES_MATCHING PATTERN "*.h*")

# test
IF (BUILD_TEST)
    INCLUDE(cmakes/sample.cmake)
    INCLUDE(cmakes/test.cmake)
    INCLUDE(cmakes/gtest.cmake)
ENDIF ()