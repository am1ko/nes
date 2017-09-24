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
    EXPECT_MEM_READ_16(0xFFFCU, 0xABCDU);

    cpu.reset();

    EXPECT_EQ(REG_PC, 0xABCDU);
    EXPECT_EQ(REG_P,  0x24U);
    EXPECT_EQ(REG_SP, 0xFDU);
    EXPECT_EQ(REG_A,  0x00U);
    EXPECT_EQ(REG_X,  0x00U);
    EXPECT_EQ(REG_Y,  0x00U);
}
