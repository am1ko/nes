#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class StxTest : public ::testing::Test {
protected:
    StxTest();
    virtual ~StxTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
