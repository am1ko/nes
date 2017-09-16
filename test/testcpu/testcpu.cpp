#include "testcpu.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

CpuTest::CpuTest() {
    // Have qux return true by default
    //ON_CALL(m_bar,qux()).WillByDefault(Return(true));
    // Have norf return false by default
    //ON_CALL(m_bar,norf()).WillByDefault(Return(false));
}

CpuTest::~CpuTest() {};

void CpuTest::SetUp() {
    cpu.reset(memory);
};

void CpuTest::TearDown() {};


TEST_F(CpuTest, ReadResetVectorToPc) {
    EXPECT_CALL(memory, read(0xFFFCU)).WillOnce(Return(0xAB));
    EXPECT_CALL(memory, read(0xFFFDU)).WillOnce(Return(0xBA));

    cpu.reset(memory);

    EXPECT_EQ(cpu.context.PC, 0xABBAU);
}

TEST_F(CpuTest, AdcImmediate) {
    {
        cpu.context.PC = 0x0600U;
        EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69));
        EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x05));
        cpu.context.A = 0x80U;

        cpu.tick(memory);

        EXPECT_EQ(cpu.context.A, 0x85U);
        EXPECT_EQ(cpu.context.PC, 0x0602U);
    }

    {
        EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69));
        EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x10));

        cpu.tick(memory);

        EXPECT_EQ(cpu.context.A, 0x95U);
        EXPECT_EQ(cpu.context.PC, 0x0604U);
    }
}

TEST_F(CpuTest, AdcImmediateCarryFlagSet) {
    cpu.context.PC = 0x0600U;
    EXPECT_CALL(memory, read(cpu.context.PC)).WillOnce(Return(0x69));
    EXPECT_CALL(memory, read(cpu.context.PC + 1)).WillOnce(Return(0x01));
    cpu.context.A = 0xFFU;

    cpu.tick(memory);

    EXPECT_EQ(cpu.context.A, 0x00U);
    EXPECT_EQ(cpu.context.P & 0x01U, 0x01U);
}