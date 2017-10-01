#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class SubroutineTest : public ::testing::Test {
protected:
    SubroutineTest();
    virtual ~SubroutineTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
