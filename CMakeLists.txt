project(rtcfg)
cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_STANDARD 17)

include_directories(include)

include(external/utils.cmake)
include(external/spdlog/check.cmake)

add_executable(test tests/unit/test.cpp)
target_link_libraries(test PUBLIC spdlog::spdlog)
target_include_directories(test PUBLIC spdlog::spdlog)