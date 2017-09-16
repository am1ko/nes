#include "imemory.h"
#include "cpu.h"

Cpu::Cpu(){};

void Cpu::reset(IMemory& memory) {
    // Read the Reset interrupt vector to PC
    context.PC = memory.read(0xFFFDU) | (memory.read(0xFFFCU) << 8);
}

void Cpu::tick(IMemory& memory) {
    // Fetch
    memory.read(context.PC);
    // TODO(amiko): decode
    // TODO(amiko): execute
    uint16_t const val = memory.read(context.PC + 1);
    context.A += val;

    if (val > 0xFFU)
    {
        context.A = 0U;
        context.P |= 1;
    }


    context.PC += 2U;
}
