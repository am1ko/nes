#include "testjmp.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
JmpTest::JmpTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
JmpTest::~JmpTest() {};

// ---------------------------------------------------------------------------------------------- //
void JmpTest::SetUp() {
    RESET_CPU(0xC000U);
};

// ---------------------------------------------------------------------------------------------- //
void JmpTest::TearDown() {};


// ---------------------------------------------------------------------------------------------- //
TEST_F(JmpTest, Absolute) {
    EXPECT_MEM_READ_8(0xC000U, 0x4CU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xC5F5U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC5F5U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(JmpTest, Indirect) {
    EXPECT_MEM_READ_8(0xC000U, 0x6CU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xC5F5U);
    EXPECT_MEM_READ_16(0xC5F5U, 0xABBAU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 5U);
    EXPECT_EQ(REG_PC, 0xABBAU);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(JmpTest, IndirectBug) {
    EXPECT_MEM_READ_8(0xC000U, 0x6CU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xD0FFU);
    EXPECT_MEM_READ_8(0xD0FFU, 0xBAU);
    EXPECT_MEM_READ_8(0xD000U, 0xABU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 5U);
    EXPECT_EQ(REG_PC, 0xABBAU);
}