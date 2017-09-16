#include "imemory.h"
#include "cpu.h"

Cpu::Cpu(){};

void Cpu::tick(CpuContext& context)
{
    // TODO(amiko): fetch
    // TODO(amiko): decode
    // TODO(amiko): execute

    context.PC++;
}
