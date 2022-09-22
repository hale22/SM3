INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(
        tests
        src/main_test.cpp src/utils.cpp
)
TARGET_LINK_LIBRARIES(tests atmmodel -lstdc++fs)

SET (TEST_COMMAND ${memcheck_command} ${CMAKE_BINARY_DIR}/project/tests/tests)

ADD_TEST(
        NAME BaseTest
        COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/project/tests/data
)