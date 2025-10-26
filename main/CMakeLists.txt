cmake_minimum_required(VERSION 3.20)

if (WIN32)
set( CMAKE_CXX_FLAGS "/Za /EHsc" )
else()
set( CMAKE_CXX_FLAGS "-Wall -Werror" )
endif()

FIND_PACKAGE( Boost )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

FIND_PACKAGE(SDL2 REQUIRED)
INCLUDE_DIRECTORIES( ${SDL2_INCLUDE_DIRS} )

add_executable(testApp
    main.cpp
)

target_link_libraries(testApp libnes)
target_link_libraries(testApp ${SDL2_LIBRARIES})

install(TARGETS testApp DESTINATION bin)