#include "testasl.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
AslTest::AslTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
AslTest::~AslTest() {};

// ---------------------------------------------------------------------------------------------- //
void AslTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with this expectation
    EXPECT_MEM_READ_16(0xFFFCU, 0xABBAU);
    cpu.reset();
    SET_REG_PC(0x0800U);
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void AslTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulator) {
    EXPECT_MEM_READ_8(REG_PC, 0x0AU);
    SET_REG_A(0x55U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0xAAU);
    EXPECT_EQ(REG_PC, 0x0801U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x0AU);
    SET_REG_A(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x0AU);
    SET_REG_A(0x40U);
    SET_ZEROF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x80U);
    EXPECT_EQ(ZEROF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorNegativeFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x0AU);
    SET_REG_A(0x40U);
    SET_NEGF(0);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x80U);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x0AU);
    SET_REG_A(0x20U);
    SET_NEGF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x40U);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorCarryFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x0AU);
    SET_REG_A(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(CARRYF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorCarryFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x0AU);
    SET_REG_A(0x02U);
    SET_CARRYF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x04U);
    EXPECT_EQ(CARRYF, false);
}


// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0x06U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_MEM_READ_8(0x000A, 0x33U);
    EXPECT_CALL(memory, write(0x000AU, 0x66U));

    cpu.tick();

    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x16U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xA0U);
    EXPECT_MEM_READ_8(0x00A3U, 0x33U);     // parameter value
    EXPECT_CALL(memory, write(0x00A3U, 0x66U));
    SET_REG_X(0x03U);

    cpu.tick();

    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0x0EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBA, 0x10U);      // parameter value
    EXPECT_MEM_WRITE_8(0xABBAU, 0x20U);

    cpu.tick();

    EXPECT_EQ(REG_PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAbsoluteXIndexed) {
    SET_REG_X(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0x1EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBA + REG_X, 0x10U);      // parameter value
    EXPECT_MEM_WRITE_8(0xABBAU + REG_X, 0x20U);

    cpu.tick();

    EXPECT_EQ(REG_PC, 0x0803U);
}
