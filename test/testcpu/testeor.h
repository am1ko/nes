#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class EorTest : public ::testing::Test {
protected:
    EorTest();
    virtual ~EorTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
