set (MUTEX_IFACE
    hierarchical.h
    )

set (MUTEX_H
    )

set (MUTEX_CPP
    hierarchical.cc
    )

add_library(mutex STATIC ${MUTEX_CPP})
