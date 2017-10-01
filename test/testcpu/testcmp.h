#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class CmpTest : public ::testing::Test {
protected:
    CmpTest();
    virtual ~CmpTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
