file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testppu ${SRCS})

TARGET_LINK_LIBRARIES(
    testppu
    libnes
    libgtest
    libgmock
)

add_test(NAME testppu
         COMMAND testppu)