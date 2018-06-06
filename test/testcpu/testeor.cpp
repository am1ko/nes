#include "testeor.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
EorTest::EorTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
EorTest::~EorTest() {};

// ---------------------------------------------------------------------------------------------- //
void EorTest::SetUp() {
    RESET_CPU(0x0800U);
};

// ---------------------------------------------------------------------------------------------- //
void EorTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorImmediate) {
    EXPECT_MEM_READ_8(REG_PC, 0x49U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xA5U);
    SET_REG_A(0xAAU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0FU);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorImmediateZeroFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x49U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x00U);
    SET_REG_A(0x00U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x02U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorImmediateZeroFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x49U);
    EXPECT_MEM_READ_8(REG_PC + 1, 2U);
    SET_REG_A(0x00U);
    SET_REG_P(0x02U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x02U);
    EXPECT_EQ(cpu.context.P & 0x02U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorImmediateNegativeFlagSet) {
    EXPECT_MEM_READ_8(REG_PC, 0x49U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x80);
    SET_REG_A(0x00U);
    SET_REG_P(0x00U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x80U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x80U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorImmediateNegativeFlagCleared) {
    EXPECT_MEM_READ_8(REG_PC, 0x49U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x06U);
    SET_REG_A(0x06U);
    SET_REG_P(0x80U);

    cpu.tick();

    EXPECT_EQ(REG_A, 0x00U);
    EXPECT_EQ(cpu.context.P & 0x80U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorZeroPage) {
    EXPECT_MEM_READ_8(REG_PC, 0x45U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x0AU);
    EXPECT_CALL(memory, read(0x000AU)).WillOnce(Return(0xA5U));     // parameter value
    SET_REG_A(0xAAU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0FU);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 3U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorZeroPageXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x55U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xA0U);
    EXPECT_CALL(memory, read(0x00A3U)).WillOnce(Return(0xA5U));     // parameter value
    SET_REG_A(0xAAU);
    SET_REG_X(0x03U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0FU);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorAbsolute) {
    EXPECT_MEM_READ_8(REG_PC, 0x4DU);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_CALL(memory, read(0xABBA)).WillOnce(Return(0xA5U));      // parameter value
    SET_REG_A(0xAAU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0FU);
    EXPECT_EQ(REG_PC, 0x0803U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorAbsoluteXIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x5DU);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_CALL(memory, read(0xABBAU + 0x03U)).WillOnce(Return(0xA5U));      // parameter value
    SET_REG_A(0xAAU);
    SET_REG_X(0x03U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0FU);
    EXPECT_EQ(cpu.context.PC, 0x0803U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorAbsoluteYIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x59U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xBAU);
    EXPECT_MEM_READ_8(REG_PC + 2, 0xABU);
    EXPECT_MEM_READ_8(0xABBA + 0x04U, 0xA5U);  // parameter value
    SET_REG_A(0xAAU);
    SET_REG_Y(0x04U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0FU);
    EXPECT_EQ(REG_PC, 0x0803U);
    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorIndexedIndirect) {
    EXPECT_MEM_READ_8(REG_PC, 0x41U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xF6U);             // F6 == addr of addr base
    EXPECT_MEM_READ_16(0x00F6U + 0x05U, 0x1111U);     // addr = read(F6 + offset)
    EXPECT_MEM_READ_8(0x1111U, 0xA5U);               // read actual parameter value
    SET_REG_A(0xAAU);
    SET_REG_X(0x05U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0FU);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 6U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(EorTest, EorIndirectIndexed) {
    EXPECT_MEM_READ_8(REG_PC, 0x51U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0xF6U);            // F6 == addr of addr base
    EXPECT_MEM_READ_16(0x00F6U, 0x1111U);            // addr = read(F6 + offset)
    EXPECT_MEM_READ_8(0x1111U + 0x04U, 0xA5U);       // read actual parameter value
    SET_REG_A(0xAAU);
    SET_REG_Y(0x04U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(REG_A, 0x0FU);
    EXPECT_EQ(REG_PC, 0x0802U);
    EXPECT_EQ(ret, 5U);
}
