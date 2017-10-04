set (TEST_NAME stack_tests)

set (TEST_CPP
    locked_tests.cpp
    )

link_directories(${LIBRARY_OUTPUT_PATH})

add_executable(${TEST_NAME} ${TEST_CPP})
target_link_libraries(${TEST_NAME} gtest gtest_main)
add_test(${TEST_NAME} ${TEST_NAME})
