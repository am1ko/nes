file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testbus ${SRCS})

TARGET_LINK_LIBRARIES(
    testbus
    libnes
    libgtest
    libgmock
)

add_test(NAME testbus
         COMMAND testbus)