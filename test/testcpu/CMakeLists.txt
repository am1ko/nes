file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testcpu ${SRCS})

TARGET_LINK_LIBRARIES(
    testcpu
    libnes
    libgtest
    libgmock
)

add_test(NAME testreset
         COMMAND testreset)
add_test(NAME testadc
         COMMAND testadc)
add_test(NAME testnop
         COMMAND testnop)
