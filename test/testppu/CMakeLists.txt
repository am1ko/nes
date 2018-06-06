file(GLOB SRCS *.cpp)

set( CMAKE_CXX_FLAGS "-Wall -Werror" )

ADD_EXECUTABLE(testppu ${SRCS})

TARGET_LINK_LIBRARIES(
    testppu
    libnes
    libgtest
    libgmock
)

add_test(NAME testppu
         COMMAND testppu)