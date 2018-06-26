set(libnes_SRCS
    cpu.cpp
    bus.cpp
    ppu.cpp
    emu.cpp
    bus_ppu.cpp
    ines_parser_ifstream.cpp
    io_registers.cpp
)

if (WIN32)
set( CMAKE_CXX_FLAGS "/Za" )
else()
set( CMAKE_CXX_FLAGS "-Wall -Werror" )
endif()

# Declare the library
add_library(libnes STATIC
    ${libnes_SRCS}
)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# Specify here the include directories exported
# by this library
target_include_directories(libnes PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
