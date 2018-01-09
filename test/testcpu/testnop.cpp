#include "testnop.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
NopTest::NopTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
NopTest::~NopTest() {};

// ---------------------------------------------------------------------------------------------- //
void NopTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0x8000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void NopTest::TearDown() {};


// ---------------------------------------------------------------------------------------------- //
TEST_F(NopTest, AdvancePc) {
    // EXPECT_CALL(memory, read(0x8000U)).WillRepeatedly(Return(0xEAU));
    EXPECT_MEM_READ_8(0x8000U, 0xEAU);
    SET_REG_A(1U);
    SET_REG_X(2U);
    SET_REG_Y(3U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(REG_PC, 0x8001U);
    EXPECT_EQ(REG_P, 0x20U);
    EXPECT_EQ(REG_A, 1U);
    EXPECT_EQ(REG_X, 2U);
    EXPECT_EQ(REG_Y, 3U);
}