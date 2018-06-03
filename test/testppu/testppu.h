#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ppu.h"
#include "mock_cpu_interrupt.h"

class PpuTest : public ::testing::Test {

protected:

    PpuTest();
    virtual ~PpuTest();

    Ppu ppu;
    MockCpuInterrupt cpu_interrupt;
};
