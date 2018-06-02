#include "testppu.h"
#include "ppu.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
PpuTest::PpuTest() {
}

// ---------------------------------------------------------------------------------------------- //
PpuTest::~PpuTest() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, Template) {
    unsigned const ret = ppu.tick();
    EXPECT_EQ(ret, 0U);
}