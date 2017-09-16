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

    context.PC++;
}
