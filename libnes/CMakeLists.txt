set(libnes_SRCS
    cpu.cpp
    bus.cpp
    ram.cpp
    rom_ifstream.cpp
    io_registers.cpp
    ppu.cpp
    bus_ppu.cpp
)

set( CMAKE_CXX_FLAGS "-Wall -Werror" )

# Declare the library
add_library(libnes STATIC
    ${libnes_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libnes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
