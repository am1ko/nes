cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 11)

project(nes_emulator)

enable_testing()

add_subdirectory(main)
add_subdirectory(test)
add_subdirectory(libnes)
