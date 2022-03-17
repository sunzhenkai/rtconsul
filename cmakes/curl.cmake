include(ExternalProject)
include(${CMAKE_CURRENT_LIST_DIR}/utils.cmake)

set(target curl)
string(REPLACE ";" "|" T_CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
set(CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${DEPS_PREFIX}
        -DCMAKE_PREFIX_PATH=${T_CMAKE_PREFIX_PATH}
        -DBUILD_STATIC_LIB=ON
        -DBUILD_SHARED_LIB=OFF)
ExternalProject_Add(
        ${target}_build
        GIT_REPOSITORY https://gitee.com/mirrors/curl.git
        GIT_TAG curl-7_81_0
        DEPENDS openssl::ssl
        CONFIGURE_COMMAND <SOURCE_DIR>/configure --with-openssl
        LIST_SEPARATOR |
        CMAKE_ARGS ${CMAKE_ARGS}
)

AddLibrary(${target} PREFIX ${DEPS_PREFIX} DEP ${target}_build SUBMODULES ${target})
