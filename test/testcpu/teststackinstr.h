#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class StackInstrTest : public ::testing::Test {
protected:
    StackInstrTest();
    virtual ~StackInstrTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
