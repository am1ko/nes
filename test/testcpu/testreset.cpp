#include "testreset.h"

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
void ResetTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with these expectations
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0x80U));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0x00U));
    cpu.reset();
    cpu.context.P = 0x00U;
};

// ---------------------------------------------------------------------------------------------- //
void ResetTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(ResetTest, ReadResetVectorToPc) {
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0xBAU));

    cpu.reset();

    EXPECT_EQ(cpu.context.PC, 0xABBAU);
}
