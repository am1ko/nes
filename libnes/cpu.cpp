#include "imemory.h"
#include "cpu.h"

Cpu::Cpu(){};

void Cpu::tick(CpuContext& context, IMemory& memory)
{
    // TODO(amiko): fetch
    memory.read(context.PC);
    // TODO(amiko): decode
    // TODO(amiko): execute

    context.PC++;
}
