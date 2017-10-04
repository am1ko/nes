#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class OrTest : public ::testing::Test {
protected:
    OrTest();
    virtual ~OrTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
