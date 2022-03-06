project(rtcfg)
cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_STANDARD 17)

set(DEPS_PREFIX ${PROJECT_SOURCE_DIR}/3rd_party)
set(DEPS_INCLUDE_DIR ${DEPS_PREFIX}/include)
set(DEPS_LIB_DIR ${DEPS_PREFIX}/lib)
set(DEPS_LIB64_DIR ${DEPS_PREFIX}/lib64)
list(APPEND CMAKE_PREFIX_PATH ${DEPS_PREFIX})

include(cmakes/spdlog.cmake)
include(cmakes/openssl.cmake)

add_executable(test tests/unit/test.cpp)
target_link_libraries(test spdlog::spdlog openssl::openssl)