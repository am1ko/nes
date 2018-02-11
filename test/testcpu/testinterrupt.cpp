#include "testinterrupt.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
InterruptTest::InterruptTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
InterruptTest::~InterruptTest() {};

// ---------------------------------------------------------------------------------------------- //
void InterruptTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0xC000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void InterruptTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(InterruptTest, RTI) {
    SET_REG_P(0x00U);
    SET_REG_SP(0xF0U);
    EXPECT_MEM_READ_8(0xC000U, 0x40U);
    EXPECT_MEM_READ_8(0x01F1U, 0xAAU);
    EXPECT_MEM_READ_16(0x01F2U, 0xC5F5U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
    EXPECT_EQ(REG_P, 0xAAU);
    EXPECT_EQ(REG_PC, 0xC5F5U);
    EXPECT_EQ(REG_SP, 0xF3U);
}
