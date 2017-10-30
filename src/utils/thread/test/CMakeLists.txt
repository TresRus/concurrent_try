set (TEST_NAME thread_tests)

set (TEST_CPP
    background_tests.cpp
    )

link_directories(${LIBRARY_OUTPUT_PATH})

add_executable(${TEST_NAME} ${TEST_CPP})
target_link_libraries(${TEST_NAME} gtest gtest_main)
target_link_libraries(${TEST_NAME} thread)
add_test(${TEST_NAME} ${TEST_NAME})
