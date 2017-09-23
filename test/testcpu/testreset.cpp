#include "testreset.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
ResetTest::ResetTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
ResetTest::~ResetTest() {};

// ---------------------------------------------------------------------------------------------- //
void ResetTest::SetUp() {
};

// ---------------------------------------------------------------------------------------------- //
void ResetTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(ResetTest, ReadResetVectorToPc) {
    EXPECT_MEM_READ_16(0xFFFCU, 0xABCDU);

    cpu.reset();

    EXPECT_EQ(cpu.context.PC, 0xABCDU);
}
