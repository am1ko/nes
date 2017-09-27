#include "testbranch.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

BranchTest::BranchTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

BranchTest::~BranchTest() {};

void BranchTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0xC100U);
    cpu.reset();
    SET_REG_P(0x00U);
};

void BranchTest::TearDown() {};


TEST_F(BranchTest, BCSPositive) {
    EXPECT_MEM_READ_8(0xC100U, 0xB0U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_CARRYF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC106U);
}

TEST_F(BranchTest, BCSNoBranch) {
    EXPECT_MEM_READ_8(0xC100U, 0xB0U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_CARRYF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC102U);
}

TEST_F(BranchTest, BCSNegative) {
    EXPECT_MEM_READ_8(0xC100U, 0xB0U);
    EXPECT_MEM_READ_8(0xC101U, 0xFFU);
    SET_CARRYF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC0FFU);
}
