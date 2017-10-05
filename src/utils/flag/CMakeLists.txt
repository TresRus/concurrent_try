set (FLAG_IFACE
    conditional.h
    flag.h
    spin.h
    )

set (FLAG_CPP
    conditional.cpp
    spin.cpp
    )

add_library(flag STATIC ${FLAG_CPP})
add_subdirectory(test)
