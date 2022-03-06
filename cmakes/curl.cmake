#message(STATUS "hello ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR}")
include(ExternalProject)

set(target openssl)
string(REPLACE ";" "|" T_CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
set(CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${DEPS_PREFIX}
        -DCMAKE_PREFIX_PATH=${T_CMAKE_PREFIX_PATH}
        -DBUILD_STATIC_LIB=ON
        -DBUILD_SHARED_LIB=OFF)
ExternalProject_Add(
        spdlog_build
        GIT_REPOSITORY https://gitee.com/mirrors/curl.git
        GIT_TAG curl-7_81_0
        DEPENDS openssl
        CONFIGURE_COMMAND <SOURCE_DIR>/configure --with-openssl
        LIST_SEPARATOR |
        CMAKE_ARGS ${CMAKE_ARGS}
)


add_library(${target} STATIC IMPORTED GLOBAL)
set_target_properties(${target} PROPERTIES
        IMPORTED_LOCATION "${DEPS_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${target}${CMAKE_STATIC_LIBRARY_SUFFIX}"
        INCLUDE_DIRECTORIES ${DEPS_INCLUDE_DIR})
add_dependencies(${target} ${target}_build)
