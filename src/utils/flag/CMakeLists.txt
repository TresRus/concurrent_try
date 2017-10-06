set (FLAG_IFACE
    flag.h
    )

set (FLAG_H
    conditional.h
    spin.h
    )

set (FLAG_CPP
    conditional.cpp
    flag.cpp
    spin.cpp
    )

add_library(flag STATIC ${FLAG_CPP})
add_subdirectory(test)
