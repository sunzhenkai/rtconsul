include(ExternalProject)
include(${CMAKE_CURRENT_LIST_DIR}/utils.cmake)

set(target openssl)
set(CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${DEPS_PREFIX}
        -DBUILD_STATIC_LIB=ON
        -DBUILD_SHARED_LIB=OFF)
ExternalProject_Add(
        ${target}_build
        GIT_REPOSITORY https://github.com/openssl/openssl.git
        GIT_TAG openssl-3.0.1
        CONFIGURE_COMMAND <SOURCE_DIR>/Configure --prefix=${DEPS_PREFIX} --openssldir=${DEPS_PREFIX}
        CMAKE_ARGS ${CMAKE_ARGS}
)

AddLibrary(${target}
        PREFIX ${DEPS_PREFIX}
        DEP ${target}_build
        SUBMODULES ssl crypto)
