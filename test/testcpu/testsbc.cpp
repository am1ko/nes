#include "testsbc.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;
// ---------------------------------------------------------------------------------------------- //
SbcTest::SbcTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
SbcTest::~SbcTest() {};

// ---------------------------------------------------------------------------------------------- //
void SbcTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with this expectation
    EXPECT_MEM_READ_16(0xFFFCU, 0xABBAU);
    cpu.reset();
    SET_REG_PC(0x0600U);
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void SbcTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
// A <= A + M + (C^1)
//     01000000 (64)
//   + 11111011 (-5)
//   +        0
//   ----------
//   1 00111011    => 59 excluding carry
TEST_F(SbcTest, SbcImmediateCarryFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0xE9U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x05U);
    SET_REG_P(0x01U);
    SET_REG_A(0x40U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A,  0x3BU);
    EXPECT_EQ(REG_PC, 0x0602U);
    EXPECT_EQ(CARRYF, true);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ret, 2U);
}

TEST_F(SbcTest, SbcImmediateCarryFlagSet2) {
    EXPECT_MEM_READ_8(REG_PC, 0xE9U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x02U);
    SET_REG_P(0x01U);
    SET_REG_A(0x70U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A,  0x6EU);
    EXPECT_EQ(REG_PC, 0x0602U);
    EXPECT_EQ(CARRYF, true);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
// A <= A + M + (C^1)
//     00000110 (6)
//   + 11111011 (-5)
//   +        1
//   ----------
//   1 00000010
TEST_F(SbcTest, SbcImmediateNoCarryFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0xE9U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x05U);
    SET_REG_P(0x00U);
    SET_REG_A(0x06U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x02U);
    EXPECT_EQ(CARRYF, true);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
// A <= A + M + (C^1)
//     00000101 (5)
//   + 11111010 (-6)
//   +        0
//   ----------
//   0 11111111
TEST_F(SbcTest, SbcImmediateNegativeResult) {
    EXPECT_MEM_READ_8(REG_PC, 0xE9U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x06U);
    SET_REG_P(0x01U);   // <- set borrow
    SET_REG_A(0x05U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0xFFU);
    EXPECT_EQ(CARRYF, false);
    EXPECT_EQ(NEGF, true);
}

// // ---------------------------------------------------------------------------------------------- //
TEST_F(SbcTest, SbcZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0xE5U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0AU); // <- zero page address
    EXPECT_MEM_READ_8(0x000AU, 0x02U);  // <- absolute address
    SET_REG_A(0x70U);
    SET_REG_P(0x01U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x6EU);
    EXPECT_EQ(REG_PC, 0x0602U);
    EXPECT_EQ(ret, 3U);
}

// // ---------------------------------------------------------------------------------------------- //
TEST_F(SbcTest, SbcZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0xF5U);
    EXPECT_MEM_READ_8(REG_PC+1, 0xA0U);
    EXPECT_MEM_READ_8(0x00A2U, 0x02U);
    SET_REG_A(0x70U);
    SET_REG_X(0x02U);
    SET_REG_P(0x01U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x6EU);
    EXPECT_EQ(REG_PC, 0x0602U);
    EXPECT_EQ(ret, 4U);
}

// // ---------------------------------------------------------------------------------------------- //
TEST_F(SbcTest, SbcAbsolute) {
    SET_REG_PC(0x0700U);
    EXPECT_MEM_READ_8(REG_PC, 0xEDU);
    EXPECT_MEM_READ_16(REG_PC+1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU, 0x02U);
    SET_REG_A(0x70U);
    SET_REG_P(0x01U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x6EU);
    EXPECT_EQ(REG_PC, 0x0703U);
    EXPECT_EQ(ret, 4U);
}

// // ---------------------------------------------------------------------------------------------- //
TEST_F(SbcTest, SbcAbsoluteXIndexed) {
    SET_REG_X(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0xFDU);
    EXPECT_MEM_READ_16(REG_PC+1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU + REG_X, 0x02U);
    SET_REG_A(0x70U);
    SET_REG_P(0x01U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x6EU);
    EXPECT_EQ(REG_PC, 0x0603U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(SbcTest, SbcAbsoluteYIndexed) {
    SET_REG_Y(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0xF9U);
    EXPECT_MEM_READ_16(REG_PC+1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU + REG_Y, 0x02U);
    SET_REG_A(0x70U);
    SET_REG_P(0x01U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x6EU);
    EXPECT_EQ(REG_PC, 0x0603U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(SbcTest, SbcIndexedIndirect) {
    SET_REG_X(0x04U);                           // index
    EXPECT_MEM_READ_8(REG_PC, 0xE1U);           // instruction
    EXPECT_MEM_READ_8(REG_PC+1, 0xF6U);         // address of base address
    EXPECT_MEM_READ_8(0x00F6U + REG_X, 0x11U);  // parameter address
    EXPECT_MEM_READ_8(0x11U, 0x02U);            // parameter value
    SET_REG_A(0x70U);
    SET_REG_P(0x01U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x6EU);
    EXPECT_EQ(REG_PC, 0x0602U);
    EXPECT_EQ(ret, 6U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(SbcTest, SbcIndirectIndexed) {
    SET_REG_Y(0x04U);                           // index
    EXPECT_MEM_READ_8(REG_PC, 0xF1U);           // instruction
    EXPECT_MEM_READ_8(REG_PC+1, 0xF6U);         // address of base address
    EXPECT_MEM_READ_8(0x00F6U, 0x11U);          // base address
    EXPECT_MEM_READ_8(0x11U + REG_Y, 0x02U);    // parameter value
    SET_REG_A(0x70U);
    SET_REG_P(0x01U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x6EU);
    EXPECT_EQ(REG_PC, 0x0602U);
    EXPECT_EQ(ret, 5U);
}
