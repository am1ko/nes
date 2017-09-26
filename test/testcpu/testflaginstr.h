#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class FlagInstrTest : public ::testing::Test {
protected:
    FlagInstrTest();
    virtual ~FlagInstrTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
