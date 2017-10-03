set (MUTEX_IFACE
    hierarchical.h
    )

set (MUTEX_H
    )

set (MUTEX_CPP
    hierarchical.cpp
    )

add_library(mutex STATIC ${MUTEX_CPP})
add_subdirectory(test)
