#include "testjsr.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
// using ::testing::AnyNumber;
using ::testing::_;

JsrTest::JsrTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

JsrTest::~JsrTest() {};

void JsrTest::SetUp() {
    EXPECT_MEM_READ_16(0xFFFCU, 0x0600U);
    cpu.reset();
    SET_REG_P(0x00U);
};

void JsrTest::TearDown() {};


TEST_F(JsrTest, Immediate) {
    SET_REG_SP(0xFFU);
    EXPECT_MEM_READ_8(0x0600U, 0x20U);
    EXPECT_MEM_READ_16(REG_PC + 1, 0x0609U);
    EXPECT_MEM_WRITE_8(0x01FFU, 0x06U);
    EXPECT_MEM_WRITE_8(0x01FEU, 0x02U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
    EXPECT_EQ(REG_PC, 0x0609U);
}