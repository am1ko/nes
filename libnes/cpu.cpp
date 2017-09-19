#include "imemory.h"
#include "cpu.h"
#include "instruction_set.h"

#define RESET_VECTOR_MSB_ADDR    (0xFFFCU)
#define RESET_VECTOR_LSB_ADDR    (0xFFFDU)

// ---------------------------------------------------------------------------------------------- //
Cpu::Cpu(IMemory& memory) : memory(memory) {
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_imp() {
    return context.PC;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_imm() {
    context.PC++;
    return context.PC - 1U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_zpg() {
    context.PC++;
    return memory.read(context.PC - 1U);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_abs() {
    context.PC += 2U;
    return memory.read(context.PC - 2U) | (memory.read(context.PC - 1U) << 8);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_zpx() {
    context.PC++;
    return memory.read(context.PC - 1U) + context.sregs[X];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_abx() {
    context.PC += 2U;
    return (memory.read(context.PC - 2U) | (memory.read(context.PC - 1) << 8)) + context.sregs[X];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_aby() {
    context.PC += 2U;
    return (memory.read(context.PC - 2U) | (memory.read(context.PC - 1U) << 8)) + context.sregs[Y];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_inx() {
    context.PC++;
    return memory.read(memory.read(context.PC - 1U) + context.sregs[X]);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_iny() {
    context.PC++;
    return memory.read(memory.read(context.PC - 1U)) + context.sregs[Y];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::ADC(uint8_t param) {
    return context.sregs[A] + param + (context.P & F_C);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::AND(uint8_t param) {
    return context.sregs[A] & param;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::NOP(uint8_t param) {
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
        if (result == 0U) {
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
    // --- FETCH & DECODE INSTRUCTION ------- //
    struct CpuInstruction const * instr = &instruction_set[memory.read(context.PC++)];

    // --- FETCH PARAMETER ADDRESS --- //
    uint16_t const param_addr = (*this.*instr->addrmode_handler)();

    // --- FETCH PARAMETER VALUE --- //
    uint8_t param = 0U;
    if (param_addr != context.PC) {
        param = memory.read(param_addr);
    } // else means no param required

    // --- EXECUTE ----------------- //
    uint16_t const result = (*this.*instr->instr_executor)(param);

    // --- UPDATE CPU STATE -------- //
    update_flags(result, instr->flags);

    // --- STORE RESULT ------------ //
    if (instr->result_reg != NO_RESULT) {
        context.sregs[instr->result_reg] = result % 256U;
    }
}

