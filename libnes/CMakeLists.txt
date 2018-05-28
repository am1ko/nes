set(libnes_SRCS
    cpu.h
    cpu.cpp
    bus.h
    bus.cpp
    ram.h
    ram.cpp
    rom_ifstream.h
    rom_ifstream.cpp
    memorymap.h
    iomemorymapped.h
)

# Declare the library
add_library(libnes STATIC
    ${libnes_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libnes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
