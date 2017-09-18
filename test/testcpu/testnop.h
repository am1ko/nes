#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class NopTest : public ::testing::Test {
protected:
    NopTest();
    virtual ~NopTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
