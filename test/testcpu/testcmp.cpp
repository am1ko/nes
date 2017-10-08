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
    EXPECT_MEM_READ_16(0xFFFCU, 0x8000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void CmpTest::TearDown() {};


// ---------------------------------------------------------------------------------------------- //
TEST_F(CmpTest, CmpImmediate) {
    SET_REG_A(0x6FU);
    SET_REG_P(0x6DU);
    EXPECT_MEM_READ_8(REG_PC, 0xC9U);
    EXPECT_MEM_READ_8(REG_PC + 1U, 0x6FU);

    int const ret = cpu.tick();

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

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(REG_PC, 0x8002U);
    EXPECT_EQ(REG_P, 0xA4U);
}
