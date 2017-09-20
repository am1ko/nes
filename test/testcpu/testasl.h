#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class AslTest : public ::testing::Test {

protected:
    AslTest();
    virtual ~AslTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
