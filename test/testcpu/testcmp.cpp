#include "testcmp.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
CmpTest::CmpTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
CmpTest::~CmpTest() {};

// ---------------------------------------------------------------------------------------------- //
void CmpTest::SetUp() {
    RESET_CPU(0x8000U);
};

// ---------------------------------------------------------------------------------------------- //
void CmpTest::TearDown() {};


// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpImmediate) {
    SET_REG_A(0x6FU);
    SET_REG_P(0x6DU);
    EXPECT_MEM_READ_8(REG_PC, 0xC9U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpImmediateCarryFlagCleared) {
    SET_REG_A(0x40U);
    SET_REG_P(0x25U);
    EXPECT_MEM_READ_8(REG_PC, 0xC9U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x41U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0xA4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpZeroPage) {
    SET_REG_A(0x6FU);
    SET_REG_P(0x6DU);
    EXPECT_MEM_READ_8(REG_PC, 0xC5U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x10U);
    EXPECT_MEM_READ_8(0x10U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpZeroPageX) {
    SET_REG_A(0x6FU);
    SET_REG_X(1U);
    SET_REG_P(0x6DU);
    EXPECT_MEM_READ_8(REG_PC, 0xD5U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x10U);
    EXPECT_MEM_READ_8(0x10U + REG_X, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpAbsolute) {
    SET_REG_A(0x6FU);
    SET_REG_P(0x6DU);
    EXPECT_MEM_READ_8(REG_PC, 0xCDU);
    EXPECT_MEM_READ_16(REG_PC + 1U, 0x0700U);
    EXPECT_MEM_READ_8(0x0700U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_PC, 0x8003U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpAbsoluteX) {
    SET_REG_A(0x6FU);
    SET_REG_X(1U);
    SET_REG_P(0x6DU);
    EXPECT_MEM_READ_8(REG_PC, 0xDDU);
    EXPECT_MEM_READ_16(REG_PC + 1U, 0x0700U);
    EXPECT_MEM_READ_8(0x0700U + REG_X, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_PC, 0x8003U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpAbsoluteY) {
    SET_REG_A(0x6FU);
    SET_REG_Y(1U);
    SET_REG_P(0x6DU);
    EXPECT_MEM_READ_8(REG_PC, 0xD9U);
    EXPECT_MEM_READ_16(REG_PC + 1U, 0x0700U);
    EXPECT_MEM_READ_8(0x0700U + REG_Y, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_PC, 0x8003U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpIndirectX) {
    SET_REG_A(0x6FU);
    SET_REG_X(1U);
    SET_REG_P(0x6DU);
    EXPECT_MEM_READ_8(REG_PC, 0xC1U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x07U);
    EXPECT_MEM_READ_16(0x07U + REG_X, 0x1111U);
    EXPECT_MEM_READ_8(0x1111U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpIndirectY) {
    SET_REG_A(0x6FU);
    SET_REG_Y(1U);
    SET_REG_P(0x6CU);
    EXPECT_MEM_READ_8(REG_PC, 0xD1U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x07U);
    EXPECT_MEM_READ_16(0x07U, 0x1133U);
    EXPECT_MEM_READ_8(0x1133U + REG_Y, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 5U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CpyImmediate) {
    SET_REG_Y(0x6FU);
    SET_REG_P(0x6CU);
    EXPECT_MEM_READ_8(REG_PC, 0xC0U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CpyZeroPage) {
    SET_REG_Y(0x6FU);
    SET_REG_P(0x6CU);
    EXPECT_MEM_READ_8(REG_PC, 0xC4U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x11U);
    EXPECT_MEM_READ_8(0x11U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CpyAbsolute) {
    SET_REG_Y(0x6FU);
    SET_REG_P(0x6CU);
    EXPECT_MEM_READ_8(REG_PC, 0xCCU);
    EXPECT_MEM_READ_16(REG_PC + 1U, 0x1111U);
    EXPECT_MEM_READ_8(0x1111U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_PC, 0x8003U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CpxImmediate) {
    SET_REG_X(0x6FU);
    SET_REG_P(0x6CU);
    EXPECT_MEM_READ_8(REG_PC, 0xE0U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CpxZeroPage) {
    SET_REG_X(0x6FU);
    SET_REG_P(0x6CU);
    EXPECT_MEM_READ_8(REG_PC, 0xE4U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x11U);
    EXPECT_MEM_READ_8(0x11U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0x6F);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CpxAbsolute) {
    SET_REG_X(0x6FU);
    SET_REG_P(0x6CU);
    EXPECT_MEM_READ_8(REG_PC, 0xECU);
    EXPECT_MEM_READ_16(REG_PC + 1U, 0x1111U);
    EXPECT_MEM_READ_8(0x1111U, 0x6FU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_PC, 0x8003U);
    EXPECT_EQ(REG_P, 0x6F);
}
