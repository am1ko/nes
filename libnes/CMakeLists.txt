cmake_minimum_required(VERSION 3.20.0)

project (libnes LANGUAGES CXX)

# if (WIN32)
# set( CMAKE_CXX_FLAGS "/Za" )
# else()
# set( CMAKE_CXX_FLAGS "-Wall -Werror -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -pedantic -Wswitch-default -Winit-self" )
# endif()

add_library(libnes STATIC
    cpu.cpp
    bus.cpp
    ppu.cpp
    emu.cpp
    bus_ppu.cpp
    ines_parser_ifstream.cpp
    rom_parser_raw.cpp
    io_registers.cpp
)

target_include_directories(libnes
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
