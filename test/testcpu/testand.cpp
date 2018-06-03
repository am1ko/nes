#include "testand.h"
#include "test_helpers.h"

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
    EXPECT_MEM_READ_16(0xFFFCU, 0x7FFU);
    EXPECT_MEM_READ_8(0x7FFU, 0xEAU);
    cpu.reset();
    (void)cpu.tick();
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void AndTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediate) {
    {
        EXPECT_MEM_READ_8(REG_PC, 0x29U);
        EXPECT_MEM_READ_8(REG_PC + 1, 0xA5U);
        SET_REG_A(0xAAU);

        int const ret = cpu.tick();

        EXPECT_EQ(ret, 2U);
        EXPECT_EQ(REG_A, 0xA0U);
        EXPECT_EQ(REG_PC, 0x0802U);
    }

    {
        EXPECT_MEM_READ_8(REG_PC, 0x29U);
        EXPECT_MEM_READ_8(REG_PC + 1, 0x20U);

        cpu.tick();

        EXPECT_EQ(REG_A, 0x20U);
        EXPECT_EQ(REG_PC, 0x0804U);
    }
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediateZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x29U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x55U);
    SET_REG_A(0xAAU);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x02U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediateZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x29U);
    EXPECT_MEM_READ_8(REG_PC + 1, 2U);
    SET_REG_A(0x03U);
    SET_REG_P(0x02U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x02U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediateNegativeFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x29U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x80);
    SET_REG_A(0x80U);
    SET_REG_P(0x00U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x80U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x80U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndImmediateNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x29U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x06U);
    SET_REG_A(0x06U);
    SET_REG_P(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x06U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0x25U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_CALL(memory, read(0x000AU)).WillOnce(Return(0x33U));     // parameter value
    SET_REG_A(0x77U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_A, 0x33U);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x35U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xA0U);
    EXPECT_CALL(memory, read(0x00A3U)).WillOnce(Return(0xC3U));     // parameter value
    SET_REG_A(0xFFU);
    SET_REG_X(0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_A, 0xC3U);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0x2DU);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_CALL(memory, read(0xABBA)).WillOnce(Return(0x10U));      // parameter value
    SET_REG_A(0x31U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_A, 0x10U);
    EXPECT_EQ(REG_PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndAbsoluteXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x3DU);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_CALL(memory, read(0xABBAU + 0x03U)).WillOnce(Return(0x10U));      // parameter value
    SET_REG_A(0x31U);
    SET_REG_X(0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_A, 0x10U);
    EXPECT_EQ(cpu.context.PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndAbsoluteYIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x39U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_MEM_READ_8(0xABBA + 0x04U, 0x21U);  // parameter value
    SET_REG_A(0x21U);
    SET_REG_Y(0x04U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
    EXPECT_EQ(REG_A, 0x21U);
    EXPECT_EQ(REG_PC, 0x0803U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndIndexedIndirect) {
    EXPECT_MEM_READ_8(REG_PC, 0x21U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xF6U);          // F6 == addr of addr base
    EXPECT_MEM_READ_16(0x00F6U + 0x05U, 0x1111U);     // addr = read(F6 + offset)
    EXPECT_MEM_READ_8(0x1111U, 0x20U);               // read actual parameter value
    SET_REG_A(0x21U);
    SET_REG_X(0x05U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
    EXPECT_EQ(REG_A, 0x20U);
    EXPECT_EQ(REG_PC, 0x0802U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(AndTest, AndIndirectIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x31U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xF6U);          // F6 == addr of addr base
    EXPECT_MEM_READ_16(0x00F6U, 0x1122U);          // addr = read(F6 + offset)
    EXPECT_MEM_READ_8(0x1122U + 0x04U, 0x20U);     // read actual parameter value
    SET_REG_A(0x21U);
    SET_REG_Y(0x04U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5U);
    EXPECT_EQ(REG_A, 0x20U);
    EXPECT_EQ(REG_PC, 0x0802U);
}