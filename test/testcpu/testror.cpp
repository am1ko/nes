
#include "testror.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
RorTest::RorTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
RorTest::~RorTest() {};

// ---------------------------------------------------------------------------------------------- //
void RorTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with this expectation
    EXPECT_MEM_READ_16(0xFFFCU, 0xABBAU);
    cpu.reset();
    SET_REG_PC(0x0800U);
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void RorTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorAccumulator) {
    EXPECT_MEM_READ_8(REG_PC, 0x6AU);
    SET_REG_A(0xAAU);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 2);
    EXPECT_EQ(REG_A, 0x55U);
    EXPECT_EQ(CARRYF, false);
    EXPECT_EQ(REG_PC, 0x0801U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorAccumulatorZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x6AU);
    SET_REG_A(0x01U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorAccumulatorZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x6AU);
    SET_REG_A(0x40U);
    SET_ZEROF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x20U);
    EXPECT_EQ(ZEROF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorAccumulatorNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x6AU);
    SET_REG_A(0x20U);
    SET_NEGF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x10U);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorAccumulatorCarryFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x6AU);
    SET_REG_A(0x01U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(CARRYF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorAccumulatorCarryToMsbAndFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x6AU);
    SET_REG_A(0x02U);
    SET_CARRYF(1);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x81U);
    EXPECT_EQ(CARRYF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0x66U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_MEM_READ_8(0x000A, 0x33U);
    EXPECT_CALL(memory, write(0x000AU, 0x19U));

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x76U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xA0U);
    EXPECT_MEM_READ_8(0x00A3U, 0x33U);     // parameter value
    EXPECT_CALL(memory, write(0x00A3U, 0x19U));
    SET_REG_X(0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0x6EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU, 0x10U);      // parameter value
    EXPECT_MEM_WRITE_8(0xABBAU, 0x08U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(REG_PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(RorTest, RorAbsoluteXIndexed) {
    SET_REG_X(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0x7EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBA + REG_X, 0x10U);      // parameter value
    EXPECT_MEM_WRITE_8(0xABBAU + REG_X, 0x08U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 7);
    EXPECT_EQ(REG_PC, 0x0803U);
}

