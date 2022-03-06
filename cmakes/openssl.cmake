#message(STATUS "hello ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR}")
include(ExternalProject)

set(target openssl)
set(CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${DEPS_PREFIX}
        -DBUILD_STATIC_LIB=ON
        -DBUILD_SHARED_LIB=OFF)
ExternalProject_Add(
        ${target}_build
        GIT_REPOSITORY https://gitee.com/mirrors/openssl.git
        GIT_TAG openssl-3.0.1
        CONFIGURE_COMMAND <SOURCE_DIR>/Configure --prefix=${DEPS_PREFIX} --openssldir=${DEPS_PREFIX} '-Wl,-rpath,$(LIBRPATH)'
        CMAKE_ARGS ${CMAKE_ARGS}
)

add_library(${target}::${target} STATIC IMPORTED GLOBAL)
set_target_properties(${target}::${target} PROPERTIES
        IMPORTED_LOCATION "${DEPS_LIB_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${target}${CMAKE_STATIC_LIBRARY_SUFFIX}"
        INCLUDE_DIRECTORIES ${DEPS_INCLUDE_DIR})
add_dependencies(${target}::${target} ${target}_build)
