#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class LoadTest : public ::testing::Test {
protected:
    LoadTest();
    virtual ~LoadTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
