#include "imemory.h"
#include "cpu.h"

Cpu::Cpu(){};

void Cpu::reset(IMemory& memory) {
    // Read the Reset interrupt vector to PC
    context.PC = memory.read(0xFFFDU) | (memory.read(0xFFFCU) << 8);
}

void Cpu::tick(IMemory& memory) {
    // fetch instruction
    uint8_t const instr = memory.read(context.PC);
    context.PC++;

    uint16_t param_addr = 0U;

    if (instr == 0x69U) {
        param_addr = context.PC;
    }
    else if (instr == 0x65U) {
        param_addr = memory.read(context.PC);
    }
    else if (instr == 0x6DU) {
        param_addr = memory.read(context.PC) | (memory.read(context.PC + 1) << 8);
        context.PC++;
    }
    else if (instr == 0x75U) {
        param_addr = memory.read(context.PC) + context.X;
    }
    else if (instr == 0x7DU) {
        param_addr = (memory.read(context.PC) | (memory.read(context.PC + 1) << 8)) + context.X;
        context.PC++;
    }
    else if (instr == 0x79U) {
        param_addr = (memory.read(context.PC) | (memory.read(context.PC + 1) << 8)) + context.Y;
        context.PC++;
    }
    else if (instr == 0x61U) {
        uint8_t const addr = memory.read(context.PC);
        param_addr = memory.read(addr + context.X);
    }
    else if (instr == 0x71U) {
        uint8_t const addr = memory.read(context.PC);
        param_addr = memory.read(addr) + context.Y;
    }

    uint16_t const result = context.A + memory.read(param_addr);
    context.PC++;

    if (result > 0xFFU) {
        context.A = 0U;
        context.P |= 1U;
    }
    else {
        context.A = result;
        context.P &= ~(1U);
    }
}
