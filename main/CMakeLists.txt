set(Main_SRCS
    main.cpp
)

if (WIN32)
set( CMAKE_CXX_FLAGS "/Za /EHsc" )
else()
set( CMAKE_CXX_FLAGS "-Wall -Werror" )
endif()

FIND_PACKAGE( Boost )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(testApp
    ${Main_SRCS}
)

target_link_libraries(testApp
    libnes
)

install(TARGETS testApp DESTINATION bin)