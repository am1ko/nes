#include "teststackinstr.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
StackInstrTest::StackInstrTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
StackInstrTest::~StackInstrTest() {};

// ---------------------------------------------------------------------------------------------- //
void StackInstrTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0x8000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void StackInstrTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(StackInstrTest, PHP) {
    SET_REG_SP(0xFFU);
    SET_REG_P(0xC0U);
    EXPECT_MEM_READ_8(0x8000U, 0x08U);
    EXPECT_MEM_WRITE_8(0x01FFU, 0xD0U);     // <-- note: bit 4 (BREAK) flag set by PHP

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0x8001U);
    EXPECT_EQ(REG_SP, 0xFEU);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StackInstrTest, PLP) {
    SET_REG_SP(0xFEU);
    SET_REG_P(0xFFU);
    EXPECT_MEM_READ_8(0x8000U, 0x28U);
    EXPECT_MEM_READ_8(0x01FFU, 0x14U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_PC, 0x8001U);
    EXPECT_EQ(REG_SP, 0xFFU);
    EXPECT_EQ(REG_P, 0x24U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StackInstrTest, PLA) {
    SET_REG_SP(0xFEU);
    SET_REG_P(0xC0U);
    SET_REG_A(0x00U);
    EXPECT_MEM_READ_8(0x8000U, 0x68U);
    EXPECT_MEM_READ_8(0x01FFU, 0xC0U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_PC, 0x8001U);
    EXPECT_EQ(REG_SP, 0xFFU);
    EXPECT_EQ(REG_A, 0xC0U);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StackInstrTest, PLAZeroFlag) {
    SET_REG_SP(0xFEU);
    SET_REG_P(0xC0U);
    SET_REG_A(0x00U);
    EXPECT_MEM_READ_8(0x8000U, 0x68U);
    EXPECT_MEM_READ_8(0x01FFU, 0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StackInstrTest, PHA) {
    SET_REG_SP(0xFFU);
    SET_REG_A(0xC0U);
    EXPECT_MEM_READ_8(REG_PC, 0x48U);
    EXPECT_MEM_WRITE_8(0x01FFU, 0xC0U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0x8001U);
    EXPECT_EQ(REG_SP, 0xFEU);
}
