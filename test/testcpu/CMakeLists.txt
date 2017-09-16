file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testcpu ${SRCS})

TARGET_LINK_LIBRARIES(testcpu
    libnes
    libgtest
    libgmock
)

add_test(NAME testcpu
         COMMAND testcpu)
