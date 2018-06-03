#include "testsubroutine.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
// using ::testing::AnyNumber;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
SubroutineTest::SubroutineTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
SubroutineTest::~SubroutineTest() {};

// ---------------------------------------------------------------------------------------------- //
void SubroutineTest::SetUp() {
    RESET_CPU(0x0800U);
};

// ---------------------------------------------------------------------------------------------- //
void SubroutineTest::TearDown() {};


// ---------------------------------------------------------------------------------------------- //
TEST_F(SubroutineTest, Jsr) {
    SET_REG_SP(0xFFU);
    EXPECT_MEM_READ_8(0x0800U, 0x20U);
    EXPECT_MEM_READ_16(REG_PC + 1, 0x0809U);
    EXPECT_MEM_WRITE_8(0x01FFU, 0x08U);
    EXPECT_MEM_WRITE_8(0x01FEU, 0x02U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
    EXPECT_EQ(REG_PC, 0x0809U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(SubroutineTest, Rts) {
    SET_REG_SP(0xFDU);
    SET_REG_PC(0x0809U);
    EXPECT_MEM_READ_8(0x0809U, 0x60U);
    EXPECT_MEM_READ_16(0x01FE, 0x0802);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
    EXPECT_EQ(REG_PC, 0x0803U);
    EXPECT_EQ(REG_SP, 0xFFU);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(SubroutineTest, RtsPageBoundary) {
    SET_REG_SP(0xFDU);
    SET_REG_PC(0x0809U);
    EXPECT_MEM_READ_8(0x0809U, 0x60U);
    EXPECT_MEM_READ_16(0x01FE, 0x05FF);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
    EXPECT_EQ(REG_PC, 0x0600U);
    EXPECT_EQ(REG_SP, 0xFFU);
}