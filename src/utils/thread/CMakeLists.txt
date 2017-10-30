set (THREAD_IFACE
    background.h
    )

set (THREAD_CPP
    background.cpp
    )

add_library(thread STATIC ${THREAD_CPP})
add_subdirectory(test)
