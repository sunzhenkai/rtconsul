file(GLOB G_TESTS_SRC "${CMAKE_SOURCE_DIR}/tests/gtest/tests*.cpp")
add_executable(rtcfg_g_tests tests/gtest/main.cpp ${SRCS_DIRS} ${G_TESTS_SRC})
target_link_libraries(rtcfg_g_tests ${EXTRA} googletest::gtest)
