#include "teststx.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

StxTest::StxTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

StxTest::~StxTest() {};

void StxTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0xC000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

void StxTest::TearDown() {};


TEST_F(StxTest, ZeroPage) {
    SET_REG_X(0x22U);
    EXPECT_MEM_READ_8(0xC000U, 0x86U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x07U);
    EXPECT_MEM_WRITE_8(0x0007U, 0x22U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
}

TEST_F(StxTest, ZeroPageYIndexed) {
    SET_REG_X(0x22U);
    SET_REG_Y(0x02U);
    EXPECT_MEM_READ_8(0xC000U, 0x96U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x07U);
    EXPECT_MEM_WRITE_8(0x0007U + REG_Y, 0x22U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
}

TEST_F(StxTest, ZeroPageAbsolute) {
    SET_REG_X(0x33U);
    EXPECT_MEM_READ_8(0xC000U, 0x8EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0x0707U);
    EXPECT_MEM_WRITE_8(0x0707U, 0x33U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
}
