file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testcpu ${SRCS})

TARGET_LINK_LIBRARIES(
    testcpu
    libnes
    libgtest
    libgmock
)

add_test(NAME testreset
         COMMAND testcpu)
add_test(NAME testadc
         COMMAND testcpu)
add_test(NAME testand
         COMMAND testcpu)
add_test(NAME testasl
         COMMAND testcpu)
add_test(NAME testnop
         COMMAND testcpu)
add_test(NAME testjmp
         COMMAND testcpu)
