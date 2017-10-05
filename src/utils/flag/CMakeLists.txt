set (FLAG_IFACE
    spin.h
    conditional.h
    )

set (FLAG_CPP
    spin.cpp
    conditional.cpp
    )

add_library(flag STATIC ${FLAG_CPP})
add_subdirectory(test)
