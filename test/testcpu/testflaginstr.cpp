#include "testflaginstr.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

FlagInstrTest::FlagInstrTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

FlagInstrTest::~FlagInstrTest() {};

void FlagInstrTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0x0600U);
    cpu.reset();
    SET_REG_P(0x00U);
};

void FlagInstrTest::TearDown() {};


TEST_F(FlagInstrTest, SetCarry) {
    EXPECT_MEM_READ_8(0x0600U, 0x38U);
    SET_CARRYF(0);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(CARRYF, true);
}

TEST_F(FlagInstrTest, ClearCarry) {
    EXPECT_MEM_READ_8(0x0600U, 0x18U);
    SET_CARRYF(1);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(CARRYF, false);
}
