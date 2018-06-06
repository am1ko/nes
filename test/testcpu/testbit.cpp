#include "testbit.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
BitTest::BitTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
BitTest::~BitTest() {};

// ---------------------------------------------------------------------------------------------- //
void BitTest::SetUp() {
    RESET_CPU(0xC000U);
};

// ---------------------------------------------------------------------------------------------- //
void BitTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(BitTest, BitZeroFlagSet) {
    SET_REG_A(0x02U);
    EXPECT_MEM_READ_8(REG_PC, 0x24U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0AU);
    EXPECT_MEM_READ_8(0x000AU, 0x01U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BitTest, BitAllFlagsSet) {
    SET_REG_A(0x02U);
    EXPECT_MEM_READ_8(REG_PC, 0x24U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0AU);
    EXPECT_MEM_READ_8(0x000AU, 0xC0U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(OVERFLOWF, true);
    EXPECT_EQ(NEGF, true);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BitTest, BitAllFlagsCleared) {
    SET_REG_A(0x02U);
    SET_REG_P(0xFFU);
    EXPECT_MEM_READ_8(REG_PC, 0x24U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0AU);
    EXPECT_MEM_READ_8(0x000AU, 0x02U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(OVERFLOWF, false);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BitTest, BitAllFlagsSetAbsolute) {
    SET_REG_A(0x02U);
    EXPECT_MEM_READ_8(REG_PC, 0x2CU);
    EXPECT_MEM_READ_16(REG_PC+1, 0x0A0AU);
    EXPECT_MEM_READ_8(0x0A0AU, 0xC0U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(OVERFLOWF, true);
    EXPECT_EQ(NEGF, true);
    EXPECT_EQ(ZEROF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BitTest, NesLog) {
    SET_REG_A(0xFFU);
    SET_REG_P(0xA4U);
    EXPECT_MEM_READ_8(REG_PC, 0x24U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x01U);
    EXPECT_MEM_READ_8(0x01U, 0xFFU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_P, 0xE4U);    // NV !Z
}