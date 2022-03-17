include(ExternalProject)
include(${CMAKE_CURRENT_LIST_DIR}/utils.cmake)

set(target spdlog)
set(CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${DEPS_PREFIX}
        -DBUILD_STATIC_LIB=ON
        -DBUILD_SHARED_LIB=OFF)
ExternalProject_Add(
        ${target}_build
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.9.2
        CMAKE_ARGS ${CMAKE_ARGS}
)

AddLibrary(${target} PREFIX ${DEPS_PREFIX} DEP ${target}_build SUBMODULES ${target})