#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class BitTest : public ::testing::Test {
protected:
    BitTest();
    virtual ~BitTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
