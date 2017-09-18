#include "testadc.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

AdcTest::AdcTest() : cpu(memory) {
    // Have qux return true by default
    //ON_CALL(m_bar,qux()).WillByDefault(Return(true));
    // Have norf return false by default
    //ON_CALL(m_bar,norf()).WillByDefault(Return(false));
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

AdcTest::~AdcTest() {};

void AdcTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with these expectations
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0xBAU));
    cpu.reset();
    cpu.context.PC = 0x0600U;
    cpu.context.P = 0x00U;
};

void AdcTest::TearDown() {};


TEST_F(AdcTest, ReadResetVectorToPc) {
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0xBAU));

    cpu.reset();

    EXPECT_EQ(cpu.context.PC, 0xABBAU);
}

TEST_F(AdcTest, AdcImmediate) {
    {
        EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
        EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x05U));
        cpu.context.A = 0x80U;

        cpu.tick();

        EXPECT_EQ(cpu.context.A, 0x85U);
        EXPECT_EQ(cpu.context.PC, 0x0602U);
    }

    {
        EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
        EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x10U));

        cpu.tick();

        EXPECT_EQ(cpu.context.A, 0x95U);
        EXPECT_EQ(cpu.context.PC, 0x0604U);
    }
}

TEST_F(AdcTest, AdcImmediateNoCarryFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x01U));
    cpu.context.A = 0x00U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x01U);
    EXPECT_EQ(cpu.context.P & 0x01U, 0x00U);
}

TEST_F(AdcTest, AdcImmediateCarryFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x01U));
    cpu.context.A = 0xFFU;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x00U);
    EXPECT_EQ(cpu.context.P & 0x01U, 0x01U);
}

TEST_F(AdcTest, AdcImmediateCarryFlagMaintained) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x01U));
    cpu.context.A = 0xFEU;
    cpu.context.P = 0x01U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x00U);
    EXPECT_EQ(cpu.context.P & 0x01U, 0x01U);
}

TEST_F(AdcTest, AdcImmediateCarryFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x01U));
    cpu.context.A = 0x02U;
    cpu.context.P = 0x01U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x04U);            // carry added to result
    EXPECT_EQ(cpu.context.P & 0x01U, 0x00U);    // carry cleared
}

TEST_F(AdcTest, AdcImmediateZeroFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x02U));
    cpu.context.A = 254U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x00U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x02U);
}

TEST_F(AdcTest, AdcImmediateZeroFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(2U));
    cpu.context.A = 0x02U;
    cpu.context.P = 0x02U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x04U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x00U);
}

TEST_F(AdcTest, AdcImmediateNegativeFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(253));
    cpu.context.A = 2U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0xFFU);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x80U);
}

TEST_F(AdcTest, AdcImmediateNegativeFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x06U));
    cpu.context.A = 253U;
    cpu.context.P = 0x02U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x03U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x00U);
}

TEST_F(AdcTest, AdcImmediateOverflowFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x06U));
    cpu.context.A = 253U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x03U);
    EXPECT_EQ(cpu.context.P & 0x40U, 0x40U);
}

TEST_F(AdcTest, AdcImmediateOverflowFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x06U));
    cpu.context.A = 0U;
    cpu.context.P = 0x40U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x06U);
    EXPECT_EQ(cpu.context.P & 0x40U, 0x00U);
}

TEST_F(AdcTest, AdcZeroPage) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x65U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x0AU));
    EXPECT_CALL(memory, read(0x000AU)).WillOnce(Return(0x02U));
    cpu.context.A = 0x70U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x72U);
    EXPECT_EQ(cpu.context.PC, 0x0602U);
}

TEST_F(AdcTest, AdcZeroPageXIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x75U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xA0U));
    EXPECT_CALL(memory, read(0x00A2U)).WillOnce(Return(0x03U));
    cpu.context.A = 0x70U;
    cpu.context.X = 0x02U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x73U);
    EXPECT_EQ(cpu.context.PC, 0x0602U);
}

TEST_F(AdcTest, AdcAbsolute) {
    cpu.context.PC = 0x0700U;
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x6DU));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xBAU));
    EXPECT_CALL(memory, read(cpu.context.PC + 2)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xABBA)).WillOnce(Return(0x10U));
    cpu.context.A = 0x21U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x31U);
    EXPECT_EQ(cpu.context.PC, 0x0703U);
}

TEST_F(AdcTest, AdcAbsoluteXIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x7DU));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xBAU));
    EXPECT_CALL(memory, read(cpu.context.PC + 2)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xABBD/* + 0x03U*/)).WillOnce(Return(0x10U));
    cpu.context.A = 0x21U;
    cpu.context.X = 0x03U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x31U);
    EXPECT_EQ(cpu.context.PC, 0x0603U);
}

TEST_F(AdcTest, AdcAbsoluteYIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x79U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xBAU));
    EXPECT_CALL(memory, read(cpu.context.PC + 2)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xABBA + 0x03U)).WillOnce(Return(0x10U));
    cpu.context.A = 0x21U;
    cpu.context.Y = 0x03U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x31U);
    EXPECT_EQ(cpu.context.PC, 0x0603U);
}

TEST_F(AdcTest, AdcIndexedIndirect) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x61U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xF6U)); // F6 == addr of addr base
    EXPECT_CALL(memory, read(0x00F6U + 0x04U)).WillOnce(Return(0x11U)); // addr = read(F6 + offset)
    EXPECT_CALL(memory, read(0x11U)).WillOnce(Return(0x20U)); // read actual parameter value
    cpu.context.A = 0x21U;
    cpu.context.X = 0x04U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x41U);
    EXPECT_EQ(cpu.context.PC, 0x0602U);
}

TEST_F(AdcTest, AdcIndirectIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x71U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xF6U)); // F6 == addr of addr base
    EXPECT_CALL(memory, read(0x00F6U)).WillOnce(Return(0x11U)); // addr = read(F6 + offset)
    EXPECT_CALL(memory, read(0x11U + 0x04U)).WillOnce(Return(0x20U)); // read actual parameter value
    cpu.context.A = 0x21U;
    cpu.context.Y = 0x04U;

    cpu.tick();

    EXPECT_EQ(cpu.context.A, 0x41U);
    EXPECT_EQ(cpu.context.PC, 0x0602U);
}