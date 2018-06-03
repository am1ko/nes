
#include "testrol.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
RolTest::RolTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
RolTest::~RolTest() {};

// ---------------------------------------------------------------------------------------------- //
void RolTest::SetUp() {
    RESET_CPU(0x0800U);
};

// ---------------------------------------------------------------------------------------------- //
void RolTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolAccumulator) {
    EXPECT_MEM_READ_8(REG_PC, 0x2AU);
    SET_REG_A(0x55U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 2);
    EXPECT_EQ(REG_A, 0xAAU);
    EXPECT_EQ(CARRYF, false);
    EXPECT_EQ(REG_PC, 0x0801U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolAccumulatorZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x2AU);
    SET_REG_A(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolAccumulatorZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x2AU);
    SET_REG_A(0x40U);
    SET_ZEROF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x80U);
    EXPECT_EQ(ZEROF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolAccumulatorNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x2AU);
    SET_REG_A(0x20U);
    SET_NEGF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x40U);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolAccumulatorCarryFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x2AU);
    SET_REG_A(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(CARRYF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolAccumulatorCarryToLsbAndFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x2AU);
    SET_REG_A(0x00U);
    SET_CARRYF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x01U);
    EXPECT_EQ(CARRYF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0x26U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_MEM_READ_8(0x000A, 0x33U);
    EXPECT_CALL(memory, write(0x000AU, 0x66U));

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x36U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xA0U);
    EXPECT_MEM_READ_8(0x00A3U, 0x33U);     // parameter value
    EXPECT_CALL(memory, write(0x00A3U, 0x66U));
    SET_REG_X(0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0x2EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU, 0x10U);      // parameter value
    EXPECT_MEM_WRITE_8(0xABBAU, 0x20U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(REG_PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RolTest, RolAbsoluteXIndexed) {
    SET_REG_X(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0x3EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBA + REG_X, 0x10U);      // parameter value
    EXPECT_MEM_WRITE_8(0xABBAU + REG_X, 0x20U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 7);
    EXPECT_EQ(REG_PC, 0x0803U);
}

