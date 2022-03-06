project(rtcfg)
cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_STANDARD 17)

include(cmakes/spdlog.cmake)

add_executable(main src/main.cpp)
target_link_libraries(main spdlog)