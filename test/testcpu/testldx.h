#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class LdxTest : public ::testing::Test {

protected:
    LdxTest();
    virtual ~LdxTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
