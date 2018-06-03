#include "testreset.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
ResetTest::ResetTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
ResetTest::~ResetTest() {};

// ---------------------------------------------------------------------------------------------- //
void ResetTest::SetUp() {};

// ---------------------------------------------------------------------------------------------- //
void ResetTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(ResetTest, RegistersSetCorrectly) {
    EXPECT_MEM_READ_16(0xFFFCU, 0xC000U);
    EXPECT_MEM_READ_8(0xC000U, 0xEAU);  // <-- NOP

    cpu.reset();
    (void)cpu.tick();

    // EXPECT_EQ(REG_PC, 0xC001U);
    // EXPECT_EQ(REG_P,  0x24U);
    // EXPECT_EQ(REG_SP, 0xFDU);
    // EXPECT_EQ(REG_A,  0x00U);
    // EXPECT_EQ(REG_X,  0x00U);
    // EXPECT_EQ(REG_Y,  0x00U);
}
