#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class AndTest : public ::testing::Test {
protected:
    AndTest();
    virtual ~AndTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
