#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ppu.h"
#include "mockmemory.h"

class PpuTest : public ::testing::Test {

protected:

    PpuTest();
    virtual ~PpuTest();

    Ppu ppu;
    MockMemory bus;
};
