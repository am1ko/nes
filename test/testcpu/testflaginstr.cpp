#include "testflaginstr.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
FlagInstrTest::FlagInstrTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
FlagInstrTest::~FlagInstrTest() {};

// ---------------------------------------------------------------------------------------------- //
void FlagInstrTest::SetUp() {
    RESET_CPU(0x0600U);
};

// ---------------------------------------------------------------------------------------------- //
void FlagInstrTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(FlagInstrTest, SetCarry) {
    EXPECT_MEM_READ_8(0x0600U, 0x38U);
    SET_CARRYF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(CARRYF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(FlagInstrTest, ClearCarry) {
    EXPECT_MEM_READ_8(0x0600U, 0x18U);
    SET_CARRYF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(CARRYF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(FlagInstrTest, SetDecimalMode) {
    SET_REG_P(0x00U);
    EXPECT_MEM_READ_8(0x0600U, 0xF8U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(DECIMALF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(FlagInstrTest, ClearDecimalMode) {
    EXPECT_MEM_READ_8(0x0600U, 0xD8U);
    SET_DECIMALF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(DECIMALF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(FlagInstrTest, ClearOverflow) {
    SET_OVERFLOWF(1);
    EXPECT_MEM_READ_8(0x0600U, 0xB8U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(OVERFLOWF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(FlagInstrTest, SetInterrupt) {
    SET_REG_P(0x00U);
    EXPECT_MEM_READ_8(0x0600U, 0x78U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(INTERRUPTF, true);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(FlagInstrTest, ClearInterrupt) {
    SET_INTERRUPTF(1);
    EXPECT_MEM_READ_8(0x0600U, 0x58U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(INTERRUPTF, false);
}
