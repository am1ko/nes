#include "testnop.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

NopTest::NopTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

NopTest::~NopTest() {};

void NopTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with these expectations
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0x80U));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0x00U));
    cpu.reset();
    cpu.context.P = 0x00U;
};

void NopTest::TearDown() {};


TEST_F(NopTest, AdvancePc) {
    EXPECT_CALL(memory, read(0x8000U)).WillRepeatedly(Return(0xEAU));
    cpu.context.sregs[A] = 1U;
    cpu.context.sregs[X] = 2U;
    cpu.context.sregs[Y] = 3U;

    cpu.tick();

    EXPECT_EQ(cpu.context.PC, 0x8001U);
    EXPECT_EQ(cpu.context.P, 0U);
    EXPECT_EQ(cpu.context.sregs[A], 1U);
    EXPECT_EQ(cpu.context.sregs[X], 2U);
    EXPECT_EQ(cpu.context.sregs[Y], 3U);
}