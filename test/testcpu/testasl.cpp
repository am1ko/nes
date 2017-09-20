#include "testasl.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
AslTest::AslTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
AslTest::~AslTest() {};

// ---------------------------------------------------------------------------------------------- //
void AslTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with these expectations
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0xBAU));
    cpu.reset();
    cpu.context.PC = 0x0800U;
    cpu.context.P = 0x00U;
};

// ---------------------------------------------------------------------------------------------- //
void AslTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulator) {
    {
        EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0AU));
        cpu.context.sregs[A] = 0x55U;

        cpu.tick();

        EXPECT_EQ(cpu.context.sregs[A], 0xAAU);
        EXPECT_EQ(cpu.context.PC, 0x0801U);
    }

    {
        EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0AU));

        cpu.tick();

        EXPECT_EQ(cpu.context.sregs[A], 0x54U);
        EXPECT_EQ(cpu.context.PC, 0x0802U);
    }
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorZeroFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0AU));
    cpu.context.sregs[A] = 0x80U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x00U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x02U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorZeroFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0AU));
    cpu.context.sregs[A] = 0x40U;
    cpu.context.P = 0x02U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x80U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorNegativeFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0AU));
    cpu.context.sregs[A] = 0x40U;
    cpu.context.P = 0x00U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x80U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x80U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorNegativeFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0AU));
    cpu.context.sregs[A] = 0x20U;
    cpu.context.P = 0x00U;
    cpu.context.P = 0x80U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x40U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorCarryFlagSet) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0AU));
    cpu.context.sregs[A] = 0x80U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x00U);
    EXPECT_EQ(cpu.context.P & 0x01U, 0x01U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAccumulatorCarryFlagCleared) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0AU));
    cpu.context.sregs[A] = 0x02U;
    cpu.context.P = 0x01U;

    cpu.tick();

    EXPECT_EQ(cpu.context.sregs[A], 0x04U);
    EXPECT_EQ(cpu.context.P & 0x01U, 0x00U);
}


// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslZeroPage) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x06U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x0AU));
    EXPECT_CALL(memory, read(0x000AU)).WillOnce(Return(0x33U));
    EXPECT_CALL(memory, write(0x000AU, 0x66U));

    cpu.tick();

    EXPECT_EQ(cpu.context.PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslZeroPageXIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x16U));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xA0U));
    EXPECT_CALL(memory, read(0x00A3U)).WillOnce(Return(0x33U));     // parameter value
    EXPECT_CALL(memory, write(0x00A3U, 0x66U));
    cpu.context.sregs[X] = 0x03U;

    cpu.tick();

    EXPECT_EQ(cpu.context.PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAbsolute) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x0EU));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xBAU));
    EXPECT_CALL(memory, read(cpu.context.PC + 2)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xABBA)).WillOnce(Return(0x10U));      // parameter value
    EXPECT_CALL(memory, write(0xABBAU, 0x20U));

    cpu.tick();

    EXPECT_EQ(cpu.context.PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AslTest, AslAbsoluteXIndexed) {
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x1EU));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0xBAU));
    EXPECT_CALL(memory, read(cpu.context.PC + 2)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xABBAU + 0x03U)).WillOnce(Return(0x10U));      // parameter value
    EXPECT_CALL(memory, write(0xABBAU + 0x03U, 0x20U));
    cpu.context.sregs[X] = 0x03U;

    cpu.tick();

    EXPECT_EQ(cpu.context.PC, 0x0803U);
}
