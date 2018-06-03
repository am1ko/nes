
#include "testinc.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;
// ---------------------------------------------------------------------------------------------- //
IncTest::IncTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
IncTest::~IncTest() {};

// ---------------------------------------------------------------------------------------------- //
void IncTest::SetUp() {
    RESET_CPU(0x0600U);
};

// ---------------------------------------------------------------------------------------------- //
void IncTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, Iny) {
    EXPECT_MEM_READ_8(REG_PC, 0xC8U);
    SET_REG_Y(0x80U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_Y,  0x81U);
    EXPECT_EQ(ret, 2);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, Dey) {
    EXPECT_MEM_READ_8(REG_PC, 0x88U);
    SET_REG_Y(0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_Y,  0xFFU);
    EXPECT_EQ(ret, 2);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, Inx) {
    EXPECT_MEM_READ_8(REG_PC, 0xE8U);
    SET_REG_X(0x80U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_X,  0x81U);
    EXPECT_EQ(ret, 2);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, Dex) {
    EXPECT_MEM_READ_8(REG_PC, 0xCAU);
    SET_REG_X(0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_X,  0xFFU);
    EXPECT_EQ(ret, 2);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, IncZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0xE6U);
    EXPECT_MEM_READ_8(REG_PC+1U, 0x55U);
    EXPECT_MEM_READ_8(0x0055U, 0x02U);
    EXPECT_MEM_WRITE_8(0x0055U, 0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, IncZeroPageZeroFlag) {
    EXPECT_MEM_READ_8(REG_PC, 0xE6U);
    EXPECT_MEM_READ_8(REG_PC+1U, 0x55U);
    EXPECT_MEM_READ_8(0x0055U, 0xFFU);
    EXPECT_MEM_WRITE_8(0x0055U, 0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(ZEROF, true);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, IncZeroPageNegative) {
    EXPECT_MEM_READ_8(REG_PC, 0xE6U);
    EXPECT_MEM_READ_8(REG_PC+1U, 0x55U);
    EXPECT_MEM_READ_8(0x0055U, 0x7FU);
    EXPECT_MEM_WRITE_8(0x0055U, 0x80U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, IncZeroPageXIndexed) {
    SET_REG_X(8U);
    EXPECT_MEM_READ_8(REG_PC, 0xF6U);
    EXPECT_MEM_READ_8(REG_PC+1U, 0x55U);
    EXPECT_MEM_READ_8(0x0055U + 8U, 0x02U);
    EXPECT_MEM_WRITE_8(0x0055U + 8U, 0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, IncAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0xEEU);
    EXPECT_MEM_READ_16(REG_PC+1U, 0x4455U);
    EXPECT_MEM_READ_8(0x4455U, 0xAAU);
    EXPECT_MEM_WRITE_8(0x4455U, 0xABU);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, IncAbsoluteXIndexed) {
    SET_REG_X(9U);
    EXPECT_MEM_READ_8(REG_PC, 0xFEU);
    EXPECT_MEM_READ_16(REG_PC+1U, 0x4455U);
    EXPECT_MEM_READ_8(0x4455U + 9U, 0xAAU);
    EXPECT_MEM_WRITE_8(0x4455U + 9U, 0xABU);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 7);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, DecZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0xC6U);
    EXPECT_MEM_READ_8(REG_PC+1U, 0x55U);
    EXPECT_MEM_READ_8(0x0055U, 0x03U);
    EXPECT_MEM_WRITE_8(0x0055U, 0x02U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, DecZeroPageZeroFlag) {
    EXPECT_MEM_READ_8(REG_PC, 0xC6U);
    EXPECT_MEM_READ_8(REG_PC+1U, 0x55U);
    EXPECT_MEM_READ_8(0x0055U, 0x01U);
    EXPECT_MEM_WRITE_8(0x0055U, 0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(ZEROF, true);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, DecZeroPageNegative) {
    EXPECT_MEM_READ_8(REG_PC, 0xC6U);
    EXPECT_MEM_READ_8(REG_PC+1U, 0x55U);
    EXPECT_MEM_READ_8(0x0055U, 0x00U);
    EXPECT_MEM_WRITE_8(0x0055U, 0xFFU);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, DecZeroPageXIndexed) {
    SET_REG_X(8U);
    EXPECT_MEM_READ_8(REG_PC, 0xD6U);
    EXPECT_MEM_READ_8(REG_PC+1U, 0x55U);
    EXPECT_MEM_READ_8(0x0055U + 8U, 0x03U);
    EXPECT_MEM_WRITE_8(0x0055U + 8U, 0x02U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, DecAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0xCEU);
    EXPECT_MEM_READ_16(REG_PC+1U, 0x4455U);
    EXPECT_MEM_READ_8(0x4455U, 0xAAU);
    EXPECT_MEM_WRITE_8(0x4455U, 0xA9U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(IncTest, DecAbsoluteXIndexed) {
    SET_REG_X(9U);
    EXPECT_MEM_READ_8(REG_PC, 0xDEU);
    EXPECT_MEM_READ_16(REG_PC+1U, 0x4455U);
    EXPECT_MEM_READ_8(0x4455U + 9U, 0xAAU);
    EXPECT_MEM_WRITE_8(0x4455U + 9U, 0xA9U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 7);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(NEGF, true);
}
