#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

// ---------------------------------------------------------------------------------------------- //
class ResetTest : public ::testing::Test {
protected:
    ResetTest();
    virtual ~ResetTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
