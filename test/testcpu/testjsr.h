#include "gtest/gtest.h"
#include "mockmemory.h"
#include "cpu.h"

class JsrTest : public ::testing::Test {
protected:
    JsrTest();
    virtual ~JsrTest();
    virtual void SetUp();
    virtual void TearDown();

    Cpu cpu;
    CpuContext context;
    MockMemory memory;
};
