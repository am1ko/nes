#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class JmpTest : public ::testing::Test {
protected:
    JmpTest();
    virtual ~JmpTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
