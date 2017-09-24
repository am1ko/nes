#include "testldx.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
LdxTest::LdxTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
LdxTest::~LdxTest() {};

// ---------------------------------------------------------------------------------------------- //
void LdxTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with this expectation
    EXPECT_MEM_READ_16(0xFFFCU, 0xC000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void LdxTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxImmediate) {
    EXPECT_MEM_READ_8(REG_PC, 0xA2U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x44U);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x44U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxImmediateZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0xA2U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x00U);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x00U);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxImmediateZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0xA2U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x01U);
    SET_ZEROF(true);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x01U);
    EXPECT_EQ(ZEROF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxImmediateNegativeFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0xA2U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x80U);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x80U);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxImmediateNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0xA2U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x01U);
    SET_NEGF(true);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x01U);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0xA6U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_MEM_READ_8(0x000A, 0x33U);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x33U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxZeroPageYIndexed) {
    SET_REG_Y(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0xB6U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_MEM_READ_8(0x000A + REG_Y, 0x33U);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x33U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0xAEU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU, 0x11U);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x11U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LdxTest, LdxAbsoluteYIndexed) {
    SET_REG_Y(0x08U);
    EXPECT_MEM_READ_8(REG_PC, 0xBEU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU + REG_Y, 0x22U);

    cpu.tick();

    EXPECT_EQ(REG_X, 0x22U);
}
