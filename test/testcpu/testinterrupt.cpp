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
TEST_F(InterruptTest, SEI) {
    SET_REG_P(0x00U);
    EXPECT_MEM_READ_8(0xC000U, 0x78U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_PC, 0xC001U);
    EXPECT_EQ(INTERRUPTF, true);
    EXPECT_EQ(ret, 2U);
}