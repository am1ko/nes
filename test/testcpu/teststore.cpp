#include "teststore.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

StoreTest::StoreTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

StoreTest::~StoreTest() {};

void StoreTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0xC000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

void StoreTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STXZeroPage) {
    SET_REG_X(0x22U);
    EXPECT_MEM_READ_8(0xC000U, 0x86U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x07U);
    EXPECT_MEM_WRITE_8(0x0007U, 0x22U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STXZeroPageYIndexed) {
    SET_REG_X(0x22U);
    SET_REG_Y(0x02U);
    EXPECT_MEM_READ_8(0xC000U, 0x96U);
    EXPECT_MEM_READ_8(REG_PC + 1, 0x07U);
    EXPECT_MEM_WRITE_8(0x0007U + REG_Y, 0x22U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STXZeroPageAbsolute) {
    SET_REG_X(0x33U);
    EXPECT_MEM_READ_8(0xC000U, 0x8EU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0x0707U);
    EXPECT_MEM_WRITE_8(0x0707U, 0x33U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
}


// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STAZeroPage) {
    SET_REG_A(0x33U);
    EXPECT_MEM_READ_8(REG_PC, 0x85U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0BU);
    EXPECT_MEM_WRITE_8(0x000BU, 0x33U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STAZeroPageX) {
    SET_REG_A(0x33U);
    SET_REG_X(0x10U);
    EXPECT_MEM_READ_8(REG_PC, 0x95U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0BU);
    EXPECT_MEM_WRITE_8(0x001BU, 0x33U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STAAbsolute) {
    SET_REG_A(0x33U);
    EXPECT_MEM_READ_8(REG_PC, 0x8DU);
    EXPECT_MEM_READ_16(REG_PC+1, 0x0B0BU);
    EXPECT_MEM_WRITE_8(0x0B0BU, 0x33U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 4U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STAAbsoluteX) {
    SET_REG_A(0x33U);
    SET_REG_X(0x01U);
    EXPECT_MEM_READ_8(REG_PC, 0x9DU);
    EXPECT_MEM_READ_16(REG_PC+1, 0x0B0BU);
    EXPECT_MEM_WRITE_8(0x0B0CU, 0x33U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STAAbsoluteY) {
    SET_REG_A(0x33U);
    SET_REG_Y(0x01U);
    EXPECT_MEM_READ_8(REG_PC, 0x99U);
    EXPECT_MEM_READ_16(REG_PC+1, 0x0B0BU);
    EXPECT_MEM_WRITE_8(0x0B0CU, 0x33U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 5U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STAIndirectX) {
    SET_REG_A(0x33U);
    SET_REG_X(0x01U);
    EXPECT_MEM_READ_8(REG_PC, 0x81U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0BU);
    EXPECT_MEM_READ_16(0x0BU + REG_X, 0xAAAAU);
    EXPECT_MEM_WRITE_8(0xAAAAU, 0x33U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(StoreTest, STAIndirectY) {
    SET_REG_A(0x33U);
    SET_REG_Y(0x01U);
    EXPECT_MEM_READ_8(REG_PC, 0x91U);
    EXPECT_MEM_READ_8(REG_PC+1, 0x0BU);
    EXPECT_MEM_READ_8(0x0BU, 0xAAU);
    EXPECT_MEM_WRITE_8(0x00AAU + REG_Y, 0x33U);

    int const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
}
