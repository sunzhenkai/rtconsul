ENABLE_TESTING()
FIND_PACKAGE(GTest CONFIG REQUIRED)

SET(GTESTS_SRCS ${PRJ_SRCS})
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/tests/gtests GTESTS_SRCS)
ADD_EXECUTABLE(GTestMain ${GTESTS_SRCS})
SET(GTEST_LIBS GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
TARGET_LINK_LIBRARIES(GTestMain PRIVATE ${GTEST_LIBS} ${DEP_LIBS})

ADD_TEST(AllTestsInMain GTestMain)

ADD_CUSTOM_COMMAND(
        TARGET GTestMain
        POST_BUILD
        COMMAND mkdir -p ${CMAKE_BINARY_DIR}/log
        # COMMAND mkdir -p ${CMAKE_BINARY_DIR}/tests/assets
        # COMMAND cp -rf ${PROJECT_SOURCE_DIR}/tests/assets/* ${CMAKE_BINARY_DIR}/tests/assets/
)
