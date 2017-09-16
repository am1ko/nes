#include "testcpu.h"

//using ::testing::Return;
using ::testing::Exactly;

CpuTest::CpuTest() {
    // Have qux return true by default
    //ON_CALL(m_bar,qux()).WillByDefault(Return(true));
    // Have norf return false by default
    //ON_CALL(m_bar,norf()).WillByDefault(Return(false));
}

CpuTest::~CpuTest() {};

void CpuTest::SetUp() {
    context.PC = 0x8000U;
};

void CpuTest::TearDown() {};

TEST_F(CpuTest, TickIncrementsProgramCounter) {
    cpu.tick(context, memory);
    EXPECT_EQ(context.PC, 0x8001U);
}

TEST_F(CpuTest, TickFetchesFromPc) {
    EXPECT_CALL(memory, read(0x8000U)).Times(Exactly(1));
    cpu.tick(context, memory);
}