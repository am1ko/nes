#include "testor.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
OrTest::OrTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
OrTest::~OrTest() {};

// ---------------------------------------------------------------------------------------------- //
void OrTest::SetUp() {
    // Suppress "uninteresting mock function call" warnings with these expectations
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0xABU));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0xBAU));
    cpu.reset();
    SET_REG_PC(0x0800U);
    SET_REG_P(0x00U);
};

// ---------------------------------------------------------------------------------------------- //
void OrTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrImmediate) {
    {
        EXPECT_MEM_READ_8(REG_PC, 0x09U);
        EXPECT_MEM_READ_8(REG_PC + 1, 0xA5U);
        SET_REG_A(0xAAU);

        int const ret = cpu.tick();

        EXPECT_EQ(REG_A, 0xAFU);
        EXPECT_EQ(REG_PC, 0x0802U);
        EXPECT_EQ(ret, 2U);
    }

    {
        EXPECT_MEM_READ_8(REG_PC, 0x09U);
        EXPECT_MEM_READ_8(REG_PC + 1, 0x20U);

        cpu.tick();

        EXPECT_EQ(REG_A, 0xAFU);
        EXPECT_EQ(REG_PC, 0x0804U);
    }
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrImmediateZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x09U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x00U);
    SET_REG_A(0x00U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x02U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrImmediateZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x09U);
    EXPECT_MEM_READ_8(REG_PC + 1, 2U);
    SET_REG_A(0x00U);
    SET_REG_P(0x02U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x02U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrImmediateNegativeFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x09U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x80);
    SET_REG_A(0x80U);
    SET_REG_P(0x00U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x80U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x80U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrImmediateNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x09U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x06U);
    SET_REG_A(0x06U);
    SET_REG_P(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x06U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0x05U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_CALL(memory, read(0x000AU)).WillOnce(Return(0x11U));     // parameter value
    SET_REG_A(0x22U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x33U);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 3U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x15U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xA0U);
    EXPECT_CALL(memory, read(0x00A3U)).WillOnce(Return(0xC3U));     // parameter value
    SET_REG_A(0x00U);
    SET_REG_X(0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0xC3U);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0x0DU);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_CALL(memory, read(0xABBA)).WillOnce(Return(0x10U));      // parameter value
    SET_REG_A(0x01U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x11U);
    EXPECT_EQ(REG_PC, 0x0803U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrAbsoluteXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x1DU);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_CALL(memory, read(0xABBAU + 0x03U)).WillOnce(Return(0x10U));      // parameter value
    SET_REG_A(0x00U);
    SET_REG_X(0x03U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x10U);
    EXPECT_EQ(cpu.context.PC, 0x0803U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrAbsoluteYIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x19U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_MEM_READ_8(0xABBA + 0x04U, 0x21U);  // parameter value
    SET_REG_A(0x00U);
    SET_REG_Y(0x04U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x21U);
    EXPECT_EQ(REG_PC, 0x0803U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrIndexedIndirect) {
    EXPECT_MEM_READ_8(REG_PC, 0x01U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xF6U);  // F6 == addr of addr base
    EXPECT_MEM_READ_8(0x00F6U + 0x05U, 0x11U);     // addr = read(F6 + offset)
    EXPECT_MEM_READ_8(0x11U, 0x20U);               // read actual parameter value
    SET_REG_A(0x00U);
    SET_REG_X(0x05U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x20U);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 6U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(OrTest, OrIndirectIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x11U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xF6U);  // F6 == addr of addr base
    EXPECT_MEM_READ_8(0x00F6U, 0x11U);             // addr = read(F6 + offset)
    EXPECT_MEM_READ_8(0x11U + 0x04U, 0x20U);       // read actual parameter value
    SET_REG_A(0x00U);
    SET_REG_Y(0x04U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x20U);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 5U);
}
