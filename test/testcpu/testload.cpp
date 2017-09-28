#include "testload.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

LoadTest::LoadTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

LoadTest::~LoadTest() {};

void LoadTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0x8000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

void LoadTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAImmediate) {
    EXPECT_MEM_READ_8(REG_PC, 0xA9U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0BU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(ret, 2);
    EXPECT_EQ(REG_PC, 0x8002U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0xA5U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0AU);
    EXPECT_MEM_READ_8(0x000AU, 0x0BU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(ret, 2);
    EXPECT_EQ(REG_PC, 0x8002U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAZeroPageX) {
    SET_REG_X(5U);
    EXPECT_MEM_READ_8(REG_PC, 0xB5U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0AU);
    EXPECT_MEM_READ_8(0x000AU + 5U, 0x0BU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(ret, 4);
    EXPECT_EQ(REG_PC, 0x8002U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0xADU);
    EXPECT_MEM_READ_16(REG_PC+1, 0x0A0AU);
    EXPECT_MEM_READ_8(0x0A0AU, 0x0BU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(ret, 4);
    EXPECT_EQ(REG_PC, 0x8003U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAAbsoluteX) {
    SET_REG_X(5U);
    EXPECT_MEM_READ_8(REG_PC, 0xBDU);
    EXPECT_MEM_READ_16(REG_PC+1, 0xA0A0U);
    EXPECT_MEM_READ_8(0xA0A5U, 0x0BU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(ret, 4);
    EXPECT_EQ(REG_PC, 0x8003U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAAbsoluteY) {
    SET_REG_Y(5U);
    EXPECT_MEM_READ_8(REG_PC, 0xB9U);
    EXPECT_MEM_READ_16(REG_PC+1, 0xA0A0U);
    EXPECT_MEM_READ_8(0xA0A5U, 0x0BU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(ret, 4);
    EXPECT_EQ(REG_PC, 0x8003U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAIndirectX) {
    SET_REG_X(0x05U);                           // index
    EXPECT_MEM_READ_8(REG_PC, 0xA1U);           // instruction
    EXPECT_MEM_READ_8(REG_PC+1, 0xA0U);         // address of base address
    EXPECT_MEM_READ_8(0x00A0U + REG_X, 0x11U);  // parameter address
    EXPECT_MEM_READ_8(0x11U, 0x0BU);            // parameter value

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(ret, 6);
    EXPECT_EQ(REG_PC, 0x8002U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAIndirectY) {
    SET_REG_Y(0x04U);                           // index
    EXPECT_MEM_READ_8(REG_PC, 0xB1U);           // instruction
    EXPECT_MEM_READ_8(REG_PC+1, 0xF6U);         // pointer to pointer to table
    EXPECT_MEM_READ_8(0x00F6U, 0x11U);          // table base address
    EXPECT_MEM_READ_8(0x11U + REG_Y, 0x0BU);    // index the table using Y

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(ret, 5);
    EXPECT_EQ(REG_PC, 0x8002U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDANoFlags) {
    EXPECT_MEM_READ_8(REG_PC, 0xA9U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0BU);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x0BU);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAImmediateNegFlag) {
    EXPECT_MEM_READ_8(REG_PC, 0xA9U);
    EXPECT_MEM_READ_8(REG_PC+1, 0xBBU);

    cpu.tick();

    EXPECT_EQ(REG_A, 0xBBU);
    EXPECT_EQ(NEGF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(LoadTest, LDAImmediateZeroFlag) {
    EXPECT_MEM_READ_8(REG_PC, 0xA9U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x00U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(ZEROF, true);
}
