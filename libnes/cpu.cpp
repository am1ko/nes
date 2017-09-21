#include "imemory.h"
#include "cpu.h"
#include "instruction_set.h"

#define RESET_VECTOR_MSB_ADDR    (0xFFFCU)
#define RESET_VECTOR_LSB_ADDR    (0xFFFDU)

#define NUM_SREGS                3

// ---------------------------------------------------------------------------------------------- //
Cpu::Cpu(IMemory& memory) : memory(memory), addr(0U) {
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_acc() {
    return context.sregs[A];
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_imp() {
    return 0UL;
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_imm() {
    addr = context.PC++;
    return memory.read(addr);
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_zpg() {
    addr = memory.read(context.PC++);
    return memory.read(addr);
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_abs() {
    context.PC += 2U;
    addr = memory.read(context.PC - 2U) | (memory.read(context.PC - 1U) << 8);
    return memory.read(addr);
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_zpx() {
    addr = memory.read(context.PC++) + context.sregs[X];
    return memory.read(addr);
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_abx() {
    context.PC += 2U;
    addr = (memory.read(context.PC - 2U) | (memory.read(context.PC - 1) << 8)) + context.sregs[X];
    return memory.read(addr);
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_aby() {
    context.PC += 2U;
    addr = (memory.read(context.PC - 2U) | (memory.read(context.PC - 1U) << 8)) + context.sregs[Y];
    return memory.read(addr);
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_inx() {
    addr = memory.read(memory.read(context.PC++) + context.sregs[X]);
    return memory.read(addr);
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Cpu::addrmode_iny() {
    addr = memory.read(memory.read(context.PC++)) + context.sregs[Y];
    return memory.read(addr);
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::resultmode_none(uint8_t result) {

}

// ---------------------------------------------------------------------------------------------- //
void Cpu::resultmode_mem(uint8_t result) {
    memory.write(addr, result);
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::resultmode_reg_a(uint8_t result) {
    context.sregs[A] = result;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::ADC(uint8_t param) const {
    return context.sregs[A] + param + (context.P & F_C);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::AND(uint8_t param) const {
    return context.sregs[A] & param;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::ASL(uint8_t param) const {
    return param << 1;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::NOP(uint8_t param) const {
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::update_flags(uint16_t result, uint8_t mask) {
    // --- CARRY --- //
    if (mask & F_C) {
        if (result > 0xFFU) {
            context.P |= F_C;
            result %= 256U;
        }
        else {
            context.P &= ~(F_C);
        }
    }

    // --- ZERO --- //
    if (mask & F_Z) {
        if ((result) == 0U) {
            context.P |= F_Z;
        }
        else {
            context.P &= ~(F_Z);
        }
    }

    // --- OVERFLOW --- //
    if (mask & F_V) {
        if ((result & 0x80U) != (context.sregs[A] & 0x80U)) {
            context.P |= F_V;
        }
        else {
            context.P &= ~(F_V);
        }
    }

    // --- NEGATIVE --- //
    if (mask & F_N) {
        if (result & 0x80U) {
            context.P |= F_N;
        }
        else {
            context.P &= ~(F_N);
        }
    }
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::reset() {
    context.PC = memory.read(RESET_VECTOR_LSB_ADDR) | (memory.read(RESET_VECTOR_MSB_ADDR) << 8);
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::tick() {
    // --- FETCH & DECODE INSTRUCTION --- //
    struct CpuInstruction const * instr = &instruction_set[memory.read(context.PC++)];

    // --- FETCH PARAMETER -------------- //
    uint8_t const param = (*this.*instr->addrmode_handler)();

    // --- EXECUTE ---------------------- //
    uint16_t const result = (*this.*instr->instr_executor)(param);

    // --- UPDATE CPU STATE ------------- //
    update_flags(result, instr->flags);

    // --- STORE RESULT ----------------- //
    (*this.*instr->result_handler)(result % 256U);
}
