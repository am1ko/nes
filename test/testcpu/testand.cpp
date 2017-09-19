#include "testand.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
AndTest::AndTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
AndTest::~AndTest() {};

// ---------------------------------------------------------------------------------------------- //
void AndTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with these expectations
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0xBAU));
    cpu.reset();
    cpu.context.PC = 0x0800U;
    cpu.context.P = 0x00U;
};

// ---------------------------------------------------------------------------------------------- //
void AndTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediate) {
    {
        EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x29U));
        EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xA5U));
        cpu.context.sregs[A] = 0xAAU;

        cpu.tick();

        EXPECT_EQ(cpu.context.sregs[A], 0xA0U);
        EXPECT_EQ(cpu.context.PC, 0x0802U);
    }

    {
        EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x29U));
        EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x20U));

        cpu.tick();

        EXPECT_EQ(cpu.context.sregs[A], 0x20U);
        EXPECT_EQ(cpu.context.PC, 0x0804U);
    }
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediateZeroFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x29U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x55U));
    cpu.context.sregs[A] = 0xAAU;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x00U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x02U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediateZeroFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x29U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(2U));
    cpu.context.sregs[A] = 0x03U;
    cpu.context.P = 0x02U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x02U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediateNegativeFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x29U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x80));
    cpu.context.sregs[A] = 0x80U;
    cpu.context.P = 0x00U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x80U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x80U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediateNegativeFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x29U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x06U));
    cpu.context.sregs[A] = 0x06U;
    cpu.context.P = 0x80U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x06U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndZeroPage) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x25U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x0AU));
    EXPECT_CALL(memory, read(0x000AU)).WillOnce(Return(0x33U));     // parameter value
    cpu.context.sregs[A] = 0x77U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x33U);
    EXPECT_EQ(cpu.context.PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndZeroPageXIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x35U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xA0U));
    EXPECT_CALL(memory, read(0x00A3U)).WillOnce(Return(0xC3U));     // parameter value
    cpu.context.sregs[A] = 0xFFU;
    cpu.context.sregs[X] = 0x03U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0xC3U);
    EXPECT_EQ(cpu.context.PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndAbsolute) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x2DU));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xBAU));
    EXPECT_CALL(memory, read(cpu.context.PC + 2)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xABBA)).WillOnce(Return(0x10U));      // parameter value
    cpu.context.sregs[A] = 0x31U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x10U);
    EXPECT_EQ(cpu.context.PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndAbsoluteXIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x3DU));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xBAU));
    EXPECT_CALL(memory, read(cpu.context.PC + 2)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xABBAU + 0x03U)).WillOnce(Return(0x10U));      // parameter value
    cpu.context.sregs[A] = 0x31U;
    cpu.context.sregs[X] = 0x03U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x10U);
    EXPECT_EQ(cpu.context.PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndAbsoluteYIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x39U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xBAU));
    EXPECT_CALL(memory, read(cpu.context.PC + 2)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xABBA + 0x04U)).WillOnce(Return(0x21U));      // parameter value
    cpu.context.sregs[A] = 0x21U;
    cpu.context.sregs[Y] = 0x04U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x21U);
    EXPECT_EQ(cpu.context.PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndIndexedIndirect) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x21U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xF6U)); // F6 == addr of addr base
    EXPECT_CALL(memory, read(0x00F6U + 0x05U)).WillOnce(Return(0x11U)); // addr = read(F6 + offset)
    EXPECT_CALL(memory, read(0x11U)).WillOnce(Return(0x20U)); // read actual parameter value
    cpu.context.sregs[A] = 0x21U;
    cpu.context.sregs[X] = 0x05U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x20U);
    EXPECT_EQ(cpu.context.PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndIndirectIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x31U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xF6U)); // F6 == addr of addr base
    EXPECT_CALL(memory, read(0x00F6U)).WillOnce(Return(0x11U)); // addr = read(F6 + offset)
    EXPECT_CALL(memory, read(0x11U + 0x04U)).WillOnce(Return(0x20U)); // read actual parameter value
    cpu.context.sregs[A] = 0x21U;
    cpu.context.sregs[Y] = 0x04U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x20U);
    EXPECT_EQ(cpu.context.PC, 0x0802U);
}