#include "testjmp.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

JmpTest::JmpTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

JmpTest::~JmpTest() {};

void JmpTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0xC000U);
    cpu.reset();
    SET_REG_P(0x00U);
};

void JmpTest::TearDown() {};


TEST_F(JmpTest, Absolute) {
    EXPECT_MEM_READ_8(0xC000U, 0x4CU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xC5F5U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 3U);
    EXPECT_EQ(REG_PC, 0xC5F5U);
}

TEST_F(JmpTest, Indirect) {
    EXPECT_MEM_READ_8(0xC000U, 0x6CU);
    EXPECT_MEM_READ_16(REG_PC + 1, 0xC5F5U);
    EXPECT_MEM_READ_16(0xC5F5U, 0xABBAU);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 5U);
    EXPECT_EQ(REG_PC, 0xABBAU);
}