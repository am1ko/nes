#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class InterruptTest : public ::testing::Test {
protected:
    InterruptTest();
    virtual ~InterruptTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
