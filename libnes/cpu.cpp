#include "imemory.h"
#include "cpu.h"

enum{
    STATUS_FLAG_POS_C = 0,
    STATUS_FLAG_POS_Z,
    STATUS_FLAG_POS_I,
    STATUS_FLAG_POS_D,
    STATUS_FLAG_POS_B,
    STATUS_FLAG_POS_UNUSED,
    STATUS_FLAG_POS_V,
    STATUS_FLAG_POS_N
};

enum {
    ADDR_MODE_CC01_INDIRECT_X,
    ADDR_MODE_CC01_ZP,
    ADDR_MODE_CC01_IMMEDIATE,
    ADDR_MODE_CC01_ABSOLUTE,
    ADDR_MODE_CC01_INDIRECT_Y,
    ADDR_MODE_CC01_ZP_X,
    ADDR_MODE_CC01_ABSOLUTE_Y,
    ADDR_MODE_CC01_ABSOLUTE_X
};

#define STATUS_FLAG_C   (1U << STATUS_FLAG_POS_C)
#define STATUS_FLAG_Z   (1U << STATUS_FLAG_POS_Z)
#define STATUS_FLAG_I   (1U << STATUS_FLAG_POS_I)
#define STATUS_FLAG_D   (1U << STATUS_FLAG_POS_D)
#define STATUS_FLAG_B   (1U << STATUS_FLAG_POS_B)
#define STATUS_FLAG_V   (1U << STATUS_FLAG_POS_V)
#define STATUS_FLAG_N   (1U << STATUS_FLAG_POS_N)

#define GET_ADDR_MODE(i)    ((i & 0x1CU) >> 2)

Cpu::Cpu(IMemory& memory) : memory(memory) {
}

uint16_t Cpu::get_cc01_param_addr(uint8_t addr_mode) {
    switch(addr_mode) {
        case ADDR_MODE_CC01_IMMEDIATE:
            return context.PC;
        case ADDR_MODE_CC01_ZP:
            return memory.read(context.PC);
        case ADDR_MODE_CC01_ABSOLUTE: {
            uint16_t const ret = memory.read(context.PC) | (memory.read(context.PC + 1) << 8);
            context.PC++;
            return ret;
        }
        case ADDR_MODE_CC01_ZP_X:
            return memory.read(context.PC) + context.X;
        case ADDR_MODE_CC01_ABSOLUTE_X: {
            uint16_t const ret =
                    (memory.read(context.PC) | (memory.read(context.PC + 1) << 8)) + context.X;
            context.PC++;
            return ret;
        }
        case ADDR_MODE_CC01_ABSOLUTE_Y: {
            uint16_t const ret = (memory.read(context.PC) | (memory.read(context.PC + 1) << 8)) + context.Y;
            context.PC++;
            return ret;
        }
        case ADDR_MODE_CC01_INDIRECT_X:
            return memory.read(memory.read(context.PC) + context.X);
        case ADDR_MODE_CC01_INDIRECT_Y:
            return memory.read(memory.read(context.PC)) + context.Y;
    }
    return 0U;
}

uint16_t Cpu::adc(uint8_t addr_mode) {
    uint16_t const param_addr = get_cc01_param_addr(addr_mode);
    uint8_t  const param      = memory.read(param_addr);
    context.PC++;
    return context.A + param + (context.P & STATUS_FLAG_C);
}

void Cpu::update_flags(uint16_t result) {
    if (context.P & STATUS_FLAG_C) {
        // carry used, clear it
         context.P &= ~(STATUS_FLAG_C);
    }

    if (result > 0xFFU) {
        result %= 256U;
        context.P |= STATUS_FLAG_C;
    }

    if (result == 0U) {
        context.P |= STATUS_FLAG_Z;
    }
    else {
        context.P &= ~(STATUS_FLAG_Z);
    }

    if ((result & 0x80U) != (context.A & 0x80U)) {
        context.P |= STATUS_FLAG_V;
    }
    else {
        context.P &= ~(STATUS_FLAG_V);
    }

    if (((context.A & 0x80U) == 0U) && ((result & 0x80U) == 0x80U)) {
        context.P |= STATUS_FLAG_N;
    }
    else {
        context.P &= ~(STATUS_FLAG_N);
    }
}

void Cpu::reset() {
    // Read the Reset interrupt vector to PC
    context.PC = memory.read(0xFFFDU) | (memory.read(0xFFFCU) << 8);
}

void Cpu::tick() {
    // fetch instruction
    uint8_t const instr = memory.read(context.PC);
    context.PC++;

    uint16_t const result = adc(GET_ADDR_MODE(instr));

    update_flags(result);

    context.A = (uint8_t)(result & 0xFFU);
}

