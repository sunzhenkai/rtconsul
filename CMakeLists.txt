project(rtcfg)
cmake_minimum_required(VERSION 3.16)
SET(CMAKE_CXX_STANDARD 17)

include_directories(include)

include(external/utils.cmake)
include(external/spdlog/check.cmake)
include(external/openssl/check.cmake)
include(external/curl/check.cmake)

aux_source_directory(src SRCS_DIRS)
aux_source_directory(src/constants SRCS_DIRS)
aux_source_directory(src/factory SRCS_DIRS)
aux_source_directory(src/model SRCS_DIRS)
aux_source_directory(src/service SRCS_DIRS)
aux_source_directory(src/http SRCS_DIRS)
aux_source_directory(src/utils SRCS_DIRS)

set(EXTRA spdlog::spdlog
        openssl::ssl
        openssl::crypto
        curl::curl)


add_executable(test tests/unit/test.cpp)
target_link_libraries(test ${EXTRA})

add_executable(example examples/example.cpp ${SRCS_DIRS})
target_link_libraries(example ${EXTRA})

add_library(rtcfg-static STATIC ${SRCS_DIRS})
target_link_libraries(rtcfg-static PRIVATE ${EXTRA})
install(TARGETS rtcfg-static LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION include/rtcfg
        FILES_MATCHING PATTERN "*.h*")