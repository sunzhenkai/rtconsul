#message(STATUS "hello ${PROJECT_SOURCE_DIR} ${CMAKE_CURRENT_LIST_DIR}")
include(ExternalProject)

set(SPDLOG_INSTALL_DIR ${PROJECT_SOURCE_DIR}/3rd_party/spdlog)
set(SPDLOG_INCLUDE_DIR ${SPDLOG_INSTALL_DIR}/include)

set(CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${SPDLOG_INSTALL_DIR}
        -DBUILD_STATIC_LIB=ON
        -DBUILD_SHARED_LIB=OFF)
ExternalProject_Add(
        spdlog_build
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.9.2
        CMAKE_ARGS ${CMAKE_ARGS}
)

add_library(spdlog STATIC IMPORTED GLOBAL)
set_target_properties(spdlog PROPERTIES
        IMPORTED_LOCATION "${SPDLOG_INSTALL_DIR}/lib/libspdlog.a"
        INCLUDE_DIRECTORIES ${SPDLOG_INCLUDE_DIR})
add_dependencies(spdlog spdlog_build)
include_directories(${SPDLOG_INCLUDE_DIR})
