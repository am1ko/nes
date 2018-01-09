#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class LsrTest : public ::testing::Test {

protected:
    LsrTest();
    virtual ~LsrTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
