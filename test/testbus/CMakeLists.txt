file(GLOB SRCS *.cpp)

set( CMAKE_CXX_FLAGS "-Wall -Werror" )

ADD_EXECUTABLE(testbus ${SRCS})

TARGET_LINK_LIBRARIES(
    testbus
    libnes
    libgtest
    libgmock
)

add_test(NAME testbus
         COMMAND testbus)