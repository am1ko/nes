#include "testinterrupt.h"
#include "test_helpers.h"

#define CLC     0x18U
#define RTI     0x40U
#define NOP     0xEAU

#define INTERRUPT_VECTOR_NMI      0xFFFAU
#define INTERRUPT_VECTOR_RESET    0xFFFCU
#define INTERRUPT_VECTOR_IRQ      0xFFFEU

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
InterruptTest::InterruptTest() : cpu(memory) {
    ON_CALL(memory, read(_)).WillByDefault(Return(0U));
}

// ---------------------------------------------------------------------------------------------- //
InterruptTest::~InterruptTest() {};

// ---------------------------------------------------------------------------------------------- //
void InterruptTest::SetUp() {
    RESET_CPU(0xC000U);
};

// ---------------------------------------------------------------------------------------------- //
void InterruptTest::TearDown() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(InterruptTest, RESETInterrupt) {
    EXPECT_MEM_READ_16(INTERRUPT_VECTOR_RESET, 0x8000U);            // <-- Read interrupt vector
    EXPECT_MEM_READ_8(0x8000U, NOP);                                // <-- First instruction

    cpu.set_interrupt_pending(CpuInterrupt::RESET);
    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U + 7U);       // <-- 7 extra cycles for interrupt latency
    EXPECT_EQ(INTERRUPTF, true);   // <-- Further interrupts disabled
    EXPECT_EQ(REG_PC, 0x8001U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(InterruptTest, NMIInterrupt) {
    uint16_t const INITIAL_PC = 0xC010U;
    uint8_t  const INITIAL_SP = 0xFDU;
    uint8_t  const INITIAL_P = F_C;

    SET_REG_SP(INITIAL_SP);
    SET_REG_P(INITIAL_P);
    SET_REG_PC(INITIAL_PC);

    EXPECT_MEM_WRITE_8(0x100U + INITIAL_SP, INITIAL_PC >> 8);       // <-- Push MSB of PC to stack
    EXPECT_MEM_WRITE_8(0x100U + INITIAL_SP-1, INITIAL_PC & 0xFFU);  // <-- Push LSB of PC to stack
    EXPECT_MEM_WRITE_8(0x100U + INITIAL_SP-2, REG_P);               // <-- Push P to stack
    EXPECT_MEM_READ_16(INTERRUPT_VECTOR_NMI, 0x8000U);              // <-- Read interrupt vector
    EXPECT_MEM_READ_8(0x8000U, RTI);                                // <-- Return from interrupt
    EXPECT_MEM_READ_8(0x100U + INITIAL_SP-2, INITIAL_P);            // <-- Pop P from stack
    EXPECT_MEM_READ_16(0x100U + INITIAL_SP-1, INITIAL_PC);          // <-- Pop PC from stack

    cpu.set_interrupt_pending(CpuInterrupt::NMI);
    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 6U + 7U);       // <-- 7 extra cycles for interrupt latency
    EXPECT_EQ(REG_PC, INITIAL_PC); // <-- PC unaffected
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(InterruptTest, NMIInterruptStatusRegisterWritten) {
    uint16_t const INITIAL_PC = 0xC010U;
    uint8_t  const INITIAL_SP = 0xFDU;
    uint8_t  const INITIAL_P = F_C;

    SET_REG_SP(INITIAL_SP);
    SET_REG_P(INITIAL_P);
    SET_REG_PC(INITIAL_PC);

    EXPECT_MEM_WRITE_8(0x100U + INITIAL_SP, INITIAL_PC >> 8);       // <-- Push MSB of PC to stack
    EXPECT_MEM_WRITE_8(0x100U + INITIAL_SP-1, INITIAL_PC & 0xFFU);  // <-- Push LSB of PC to stack
    EXPECT_MEM_WRITE_8(0x100U + INITIAL_SP-2, REG_P);               // <-- Push P to stack
    EXPECT_MEM_READ_16(INTERRUPT_VECTOR_NMI, 0x8000U);              // <-- Read interrupt vector
    EXPECT_MEM_READ_8(0x8000U, CLC);                                // <-- Clear CARRY flag
    EXPECT_MEM_READ_8(0x8001U, RTI);                                // <-- Return from interrupt
    EXPECT_MEM_READ_8(0x100U + INITIAL_SP-2, INITIAL_P);            // <-- Pop P from stack
    EXPECT_MEM_READ_16(0x100U + INITIAL_SP-1, INITIAL_PC);          // <-- Pop PC from stack

    cpu.set_interrupt_pending(CpuInterrupt::NMI);
    (void)cpu.tick();
    (void)cpu.tick();

    EXPECT_EQ(CARRYF, true);       // <-- P unaffected (carry flag was cleared in interrupt)
    EXPECT_EQ(INTERRUPTF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(InterruptTest, IRQInterrupt) {
    EXPECT_MEM_READ_16(INTERRUPT_VECTOR_IRQ, 0x8000U);            // <-- Read interrupt vector
    EXPECT_MEM_READ_8(0x8000U, NOP);                              // <-- First instruction

    cpu.set_interrupt_pending(CpuInterrupt::IRQ);
    unsigned const ret = cpu.tick();


    EXPECT_EQ(INTERRUPTF, true);   // <-- Further interrupts disabled
    EXPECT_EQ(ret, 2U + 7U);       // <-- 7 extra cycles for interrupt latency
    EXPECT_EQ(REG_PC, 0x8001U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(InterruptTest, IRQInterruptMasked) {
    EXPECT_MEM_READ_8(0xC000U, NOP);

    SET_REG_P(F_I);         // <-- interrupts disabled

    cpu.set_interrupt_pending(CpuInterrupt::IRQ);
    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 2U);
    EXPECT_EQ(REG_PC, 0xC001U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(InterruptTest, RTI) {
    SET_REG_P(0x00U);
    SET_REG_SP(0xF0U);
    EXPECT_MEM_READ_8(0xC000U, 0x40U);
    EXPECT_MEM_READ_8(0x01F1U, 0xAAU);
    EXPECT_MEM_READ_16(0x01F2U, 0xC5F5U);

    unsigned const ret = cpu.tick();

    EXPECT_EQ(ret, 6U);
    EXPECT_EQ(REG_P, 0xAAU);
    EXPECT_EQ(REG_PC, 0xC5F5U);
    EXPECT_EQ(REG_SP, 0xF3U);
}
