#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class StoreTest : public ::testing::Test {
protected:
    StoreTest();
    virtual ~StoreTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
