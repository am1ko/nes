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

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BCSPositive) {
    EXPECT_MEM_READ_8(0xC100U, 0xB0U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_CARRYF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC106U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BCSNoBranch) {
    EXPECT_MEM_READ_8(0xC100U, 0xB0U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_CARRYF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC102U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BCSNegative) {
    EXPECT_MEM_READ_8(0xC100U, 0xB0U);
    EXPECT_MEM_READ_8(0xC101U, 0xFFU);
    SET_CARRYF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC0FFU);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BCCPositive) {
    EXPECT_MEM_READ_8(0xC100U, 0x90U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_CARRYF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC106U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BEQPositive) {
    EXPECT_MEM_READ_8(0xC100U, 0xF0U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_ZEROF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC106U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BEQNoBranch) {
    EXPECT_MEM_READ_8(0xC100U, 0xF0U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_ZEROF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC102U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BNEPositive) {
    EXPECT_MEM_READ_8(0xC100U, 0xD0U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_ZEROF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC106U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BNENoBranch) {
    EXPECT_MEM_READ_8(0xC100U, 0xD0U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_ZEROF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC102U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BVSPositive) {
    EXPECT_MEM_READ_8(0xC100U, 0x70U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_OVERFLOWF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC106U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BVSNoBranch) {
    EXPECT_MEM_READ_8(0xC100U, 0x70U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_OVERFLOWF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC102U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BVCPositive) {
    EXPECT_MEM_READ_8(0xC100U, 0x50U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_OVERFLOWF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC106U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BVCNoBranch) {
    EXPECT_MEM_READ_8(0xC100U, 0x50U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_OVERFLOWF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC102U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BPLPositive) {
    EXPECT_MEM_READ_8(0xC100U, 0x10U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_NEGF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC106U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BranchTest, BPLNoBranch) {
    EXPECT_MEM_READ_8(0xC100U, 0x10U);
    EXPECT_MEM_READ_8(0xC101U, 0x04U);
    SET_NEGF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC102U);
}