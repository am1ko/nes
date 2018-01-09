#include "testlsr.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
LsrTest::LsrTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
LsrTest::~LsrTest() {};

// ---------------------------------------------------------------------------------------------- //
void LsrTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with this expectation
    EXPECT_MEM_READ_16(0xFFFCU, 0xABBAU);
    cpu.reset();
    SET_REG_PC(0x0800U);
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void LsrTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrAccumulator) {
    EXPECT_MEM_READ_8(REG_PC, 0x4AU);
    SET_REG_A(0xAAU);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 2);
    EXPECT_EQ(REG_A, 0x55U);
    EXPECT_EQ(CARRYF, false);
    EXPECT_EQ(REG_PC, 0x0801U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrAccumulatorZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x4AU);
    SET_REG_A(0x01U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrAccumulatorZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x4AU);
    SET_REG_A(0x40U);
    SET_ZEROF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x20U);
    EXPECT_EQ(ZEROF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrAccumulatorNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x4AU);
    SET_REG_A(0x20U);
    SET_NEGF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x10U);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrAccumulatorCarryFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x4AU);
    SET_REG_A(0x01U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(CARRYF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrAccumulatorCarryFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x4AU);
    SET_REG_A(0x02U);
    SET_CARRYF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x01U);
    EXPECT_EQ(CARRYF, false);
}


// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0x46U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_MEM_READ_8(0x000A, 0x33U);
    EXPECT_CALL(memory, write(0x000AU, 0x19U));

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x56U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xA0U);
    EXPECT_MEM_READ_8(0x00A3U, 0x33U);     // parameter value
    EXPECT_CALL(memory, write(0x00A3U, 0x19U));
    SET_REG_X(0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0x4EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU, 0x10U);      // parameter value
    EXPECT_MEM_WRITE_8(0xABBAU, 0x08U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(REG_PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LsrTest, LsrAbsoluteXIndexed) {
    SET_REG_X(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0x5EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBA + REG_X, 0x10U);      // parameter value
    EXPECT_MEM_WRITE_8(0xABBAU + REG_X, 0x08U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 7);
    EXPECT_EQ(REG_PC, 0x0803U);
}
