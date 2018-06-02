#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ppu.h"

class PpuTest : public ::testing::Test {

protected:

    PpuTest();
    virtual ~PpuTest();

    Ppu ppu;
};
