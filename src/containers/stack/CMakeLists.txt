set (STACK_IFACE
    stack.h
    )

set (STACK_H
    )

set (STACK_CPP
    )

link_directories(${LIBRARY_OUTPUT_PATH})
cxx_test(locked_stack_tests gtest_main)
