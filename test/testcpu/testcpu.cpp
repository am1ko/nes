#include "testcpu.h"

using ::testing::Return;
using ::testing::Exactly;

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

TEST_F(CpuTest, TickIncrementsProgramCounter) {
    cpu.context.PC = 0x8000U;
    EXPECT_CALL(memory, read(0x8000U));

    cpu.tick(memory);

    EXPECT_EQ(cpu.context.PC, 0x8001U);
}