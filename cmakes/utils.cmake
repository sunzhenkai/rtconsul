macro(AddLibrary MODULE)
    set(options NONE)
    set(oneValueArgs PREFIX DEP)
    set(multiValueArgs SUBMODULES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    message(STATUS "AddLibrary MODULE=${MODULE} PREFIX=${ARG_PREFIX} DEP=${ARG_DEP} SUBMODULES=${ARG_SUBMODULES}")


    if ("${ARG_PREFIX}" STREQUAL "")
        message(FATAL_ERROR "PREFIX should not be empty")
    endif ()
    foreach (I IN LISTS ARG_SUBMODULES)
        set(TGT ${MODULE}::${I})
        message(STATUS "AddLibrary TARGET=${TGT}")
        add_library(${TGT} STATIC IMPORTED GLOBAL)
        set_target_properties(${TGT} PROPERTIES
                IMPORTED_LOCATION "${ARG_PREFIX}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}${I}${CMAKE_STATIC_LIBRARY_SUFFIX}"
                INCLUDE_DIRECTORIES ${ARG_PREFIX}/include)
        add_dependencies(${TGT} ${ARG_DEP})
        include_directories(${ARG_PREFIX}/include)
    endforeach ()
endmacro(AddLibrary)