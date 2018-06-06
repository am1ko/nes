file(GLOB SRCS *.cpp)

set( CMAKE_CXX_FLAGS "-Wall -Werror" )

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
add_test(NAME testlsr
         COMMAND testcpu)
add_test(NAME testnop
         COMMAND testcpu)
add_test(NAME testjmp
         COMMAND testcpu)
add_test(NAME testldx
         COMMAND testcpu)
add_test(NAME testsubroutine
         COMMAND testcpu)
add_test(NAME testflaginstr
         COMMAND testcpu)
add_test(NAME testbranch
         COMMAND testcpu)
add_test(NAME testload
         COMMAND testcpu)
add_test(NAME teststore
         COMMAND testcpu)
add_test(NAME testbit
         COMMAND testcpu)
add_test(NAME testinterrupt
         COMMAND testcpu)
add_test(NAME teststackinstr
         COMMAND testcpu)
add_test(NAME testcmp
         COMMAND testcpu)
add_test(NAME testor
         COMMAND testcpu)
add_test(NAME testeor
         COMMAND testcpu)
add_test(NAME testsbc
         COMMAND testcpu)
add_test(NAME testinc
         COMMAND testcpu)
add_test(NAME testtransfer
         COMMAND testcpu)
add_test(NAME testror
         COMMAND testcpu)
add_test(NAME testrol
         COMMAND testcpu)