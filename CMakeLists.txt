cmake_minimum_required(VERSION 3.20)

set (CMAKE_CXX_STANDARD 17)

project(nes_emulator)

enable_testing()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(libnes)
