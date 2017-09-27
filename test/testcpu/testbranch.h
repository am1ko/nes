#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class BranchTest : public ::testing::Test {
protected:
    BranchTest();
    virtual ~BranchTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
