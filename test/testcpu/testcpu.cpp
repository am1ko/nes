#include "cpu.h"
#include "testcpu.h"

//using ::testing::Return;

CpuTest::CpuTest() {
    // Have qux return true by default
    //ON_CALL(m_bar,qux()).WillByDefault(Return(true));
    // Have norf return false by default
    //ON_CALL(m_bar,norf()).WillByDefault(Return(false));
}

CpuTest::~CpuTest() {};

void CpuTest::SetUp() {};

void CpuTest::TearDown() {};

TEST_F(CpuTest, ByDefaultBazTrueIsTrue) {
    Cpu cpu;
    CpuContext context;
    context.PC = 0x8000U;

    cpu.tick(context);

    EXPECT_EQ(context.PC, 0x8001U);
}


