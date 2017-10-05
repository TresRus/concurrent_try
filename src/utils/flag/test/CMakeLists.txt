set (TEST_NAME flag_tests)

set (TEST_CPP
    spin_tests.cpp
    )

link_directories(${LIBRARY_OUTPUT_PATH})

add_executable(${TEST_NAME} ${TEST_CPP})
target_link_libraries(${TEST_NAME} gtest gtest_main)
target_link_libraries(${TEST_NAME} flag)
add_test(${TEST_NAME} ${TEST_NAME})
