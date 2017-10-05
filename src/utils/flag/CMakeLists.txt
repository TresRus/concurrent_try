set (FLAG_IFACE
    spin.h
    )

set (FLAG_CPP
    spin.cpp
    )

add_library(flag STATIC ${FLAG_CPP})
add_subdirectory(test)
