
#include "testinc.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;
// ---------------------------------------------------------------------------------------------- //
IncTest::IncTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
IncTest::~IncTest() {};

// ---------------------------------------------------------------------------------------------- //
void IncTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with this expectation
    EXPECT_MEM_READ_16(0xFFFCU, 0xABBAU);
    cpu.reset();
    SET_REG_PC(0x0600U);
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void IncTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, Iny) {
    EXPECT_MEM_READ_8(REG_PC, 0xC8U);
    SET_REG_Y(0x80U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_Y,  0x81U);
    EXPECT_EQ(ret, 2);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

