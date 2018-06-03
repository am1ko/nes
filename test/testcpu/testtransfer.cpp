#include "testtransfer.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;
// ---------------------------------------------------------------------------------------------- //
TransferTest::TransferTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
TransferTest::~TransferTest() {};

// ---------------------------------------------------------------------------------------------- //
void TransferTest::SetUp() {
    RESET_CPU(0x0700U);
};

// ---------------------------------------------------------------------------------------------- //
void TransferTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TayNegative) {
    EXPECT_MEM_READ_8(REG_PC, 0xA8U);
    SET_REG_A(0x80U);
    SET_REG_Y(0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_Y,  0x80U);
    EXPECT_EQ(NEGF, true);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TayZero) {
    EXPECT_MEM_READ_8(REG_PC, 0xA8U);
    SET_REG_A(0x00U);
    SET_REG_Y(0xFFU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_Y,  0x00U);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, true);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TyaZero) {
    EXPECT_MEM_READ_8(REG_PC, 0x98U);
    SET_REG_A(0x80U);
    SET_REG_Y(0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A,  0x00U);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, true);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TyaNegative) {
    EXPECT_MEM_READ_8(REG_PC, 0x98U);
    SET_REG_A(0x00U);
    SET_REG_Y(0xFFU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A,  0xFFU);
    EXPECT_EQ(NEGF, true);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TaxNegative) {
    EXPECT_MEM_READ_8(REG_PC, 0xAAU);
    SET_REG_A(0x80U);
    SET_REG_X(0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_X,  0x80U);
    EXPECT_EQ(NEGF, true);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TaxZero) {
    EXPECT_MEM_READ_8(REG_PC, 0xAAU);
    SET_REG_A(0x00U);
    SET_REG_X(0xFFU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_X,  0x00U);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, true);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TxaNegative) {
    EXPECT_MEM_READ_8(REG_PC, 0x8AU);
    SET_REG_A(0x00U);
    SET_REG_X(0xFFU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A,  0xFFU);
    EXPECT_EQ(NEGF, true);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TxaZero) {
    EXPECT_MEM_READ_8(REG_PC, 0x8AU);
    SET_REG_A(0x80U);
    SET_REG_X(0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_A,  0x00U);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, true);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TsxNegative) {
    EXPECT_MEM_READ_8(REG_PC, 0xBAU);
    SET_REG_X(0x00U);
    SET_REG_SP(0xFFU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_X,  0xFFU);
    EXPECT_EQ(NEGF, true);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TsxZero) {
    EXPECT_MEM_READ_8(REG_PC, 0xBAU);
    SET_REG_X(0x80U);
    SET_REG_SP(0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_X,  0x00U);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, true);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TxsNegative) {
    EXPECT_MEM_READ_8(REG_PC, 0x9AU);
    SET_REG_X(0x80U);
    SET_REG_SP(0x00U);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_SP,  0x80U);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(ret, 2U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(TransferTest, TxsZero) {
    EXPECT_MEM_READ_8(REG_PC, 0x9AU);
    SET_REG_X(0x00U);
    SET_REG_SP(0xFFU);

    int const ret = cpu.tick();

    EXPECT_EQ(REG_SP,  0x00U);
    EXPECT_EQ(NEGF, false);
    EXPECT_EQ(ZEROF, false);
    EXPECT_EQ(ret, 2U);
}
