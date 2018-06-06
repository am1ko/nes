set(Main_SRCS
    main.cpp
)

set( CMAKE_CXX_FLAGS "-Wall -Werror" )

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(testApp
    ${Main_SRCS}
)

target_link_libraries(testApp
    libnes
)

install(TARGETS testApp DESTINATION bin)