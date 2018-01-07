#include "testadc.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;
// ---------------------------------------------------------------------------------------------- //
AdcTest::AdcTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
AdcTest::~AdcTest() {};

// ---------------------------------------------------------------------------------------------- //
void AdcTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with this expectation
    EXPECT_MEM_READ_16(0xFFFCU, 0xABBAU);
    cpu.reset();
    SET_REG_PC(0x0600U);
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void AdcTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediate) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x05U);
    SET_REG_A(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A,  0x85U);
    EXPECT_EQ(REG_PC, 0x0602U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediate2) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x80U);
    SET_REG_A(0x7FU);
    SET_REG_P(0x64U);

    cpu.tick();

    EXPECT_EQ(REG_A,  0xFFU);
    EXPECT_EQ(REG_P,  0xA4U);
    EXPECT_EQ(REG_PC, 0x0602U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateNoCarryFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x01U);
    SET_REG_A(0x00U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x01U);
    EXPECT_EQ(CARRYF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateCarryFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x01U);
    SET_REG_A(0xFFU);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(CARRYF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateCarryFlagMaintained) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x01U);
    SET_REG_A(0xFEU);
    cpu.context.P = 0x01U;

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(CARRYF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateCarryFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x01U);
    SET_REG_A(0x02U);
    cpu.context.P = 0x01U;

    cpu.tick();

    EXPECT_EQ(REG_A, 0x04U);
    EXPECT_EQ(CARRYF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x02U);
    SET_REG_A(0xFEU);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x02U);
    SET_REG_A(0x02U);
    cpu.context.P = 0x02U;

    cpu.tick();

    EXPECT_EQ(REG_A, 0x04U);
    EXPECT_EQ(ZEROF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateNegativeFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 253);
    SET_REG_A(0x02U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0xFFU);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x06U);
    SET_REG_A(253U);
    cpu.context.P = 0x80U;

    cpu.tick();

    EXPECT_EQ(REG_A, 0x03U);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateOverflowFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x81U);
    SET_REG_A(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x01U);
    EXPECT_EQ(OVERFLOWF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcImmediateOverflowFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x06U);
    SET_REG_A(0U);
    cpu.context.P = 0x40U;

    cpu.tick();

    EXPECT_EQ(REG_A, 0x06U);
    EXPECT_EQ(OVERFLOWF, false);
}

// ---------------------------------------------------------------------------------------------- //
//    carry in to msb is 1
//    carry out of msb is 1
//    ovf = carry_in XOR carry_out
//   0111 1111
// + 1000 0000
// +         1
// -----------
// 1 0000 0000
TEST_F(AdcTest, AdcImmediateOverflowFlagCleared2) {
    EXPECT_MEM_READ_8(REG_PC, 0x69U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x80U);  // <- negative (-128)
    SET_REG_A(0x7FU);                    // <- positive (127)
    SET_REG_P(0x25U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(OVERFLOWF, false);
}


// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0x65U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0AU);
    EXPECT_MEM_READ_8(0x000AU, 0x02U);
    SET_REG_A(0x70U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x72U);
    EXPECT_EQ(REG_PC, 0x0602U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x75U);
    EXPECT_MEM_READ_8(REG_PC+1, 0xA0U);
    EXPECT_MEM_READ_8(0x00A2U, 0x03U);
    SET_REG_A(0x70U);
    SET_REG_X(0x02U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x73U);
    EXPECT_EQ(REG_PC, 0x0602U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcAbsolute) {
    SET_REG_PC(0x0700U);
    EXPECT_MEM_READ_8(REG_PC, 0x6DU);
    EXPECT_MEM_READ_16(REG_PC+1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU, 0x10U);
    SET_REG_A(0x21U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x31U);
    EXPECT_EQ(REG_PC, 0x0703U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcAbsoluteXIndexed) {
    SET_REG_X(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0x7DU);
    EXPECT_MEM_READ_16(REG_PC+1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU + REG_X, 0x10U);
    SET_REG_A(0x21U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x31U);
    EXPECT_EQ(REG_PC, 0x0603U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcAbsoluteYIndexed) {
    SET_REG_Y(0x03U);
    EXPECT_MEM_READ_8(REG_PC, 0x79U);
    EXPECT_MEM_READ_16(REG_PC+1, 0xABBAU);
    EXPECT_MEM_READ_8(0xABBAU + REG_Y, 0x10U);
    SET_REG_A(0x21U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x31U);
    EXPECT_EQ(REG_PC, 0x0603U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcIndexedIndirect) {
    SET_REG_X(0x04U);                           // index
    EXPECT_MEM_READ_8(REG_PC, 0x61U);           // instruction
    EXPECT_MEM_READ_8(REG_PC+1, 0xF6U);         // address of base address
    EXPECT_MEM_READ_8(0x00F6U + REG_X, 0x11U);  // parameter address
    EXPECT_MEM_READ_8(0x11U, 0x20U);            // parameter value
    SET_REG_A(0x21U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x41U);
    EXPECT_EQ(REG_PC, 0x0602U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AdcTest, AdcIndirectIndexed) {
    SET_REG_Y(0x04U);                           // index
    EXPECT_MEM_READ_8(REG_PC, 0x71U);           // instruction
    EXPECT_MEM_READ_8(REG_PC+1, 0xF6U);         // address of base address
    EXPECT_MEM_READ_8(0x00F6U, 0x11U);          // base address
    EXPECT_MEM_READ_8(0x11U + REG_Y, 0x20U);    // parameter value
    SET_REG_A(0x21U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x41U);
    EXPECT_EQ(REG_PC, 0x0602U);
}
