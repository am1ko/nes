#ifndef CPU_H
#define CPU_H

#include <cstdint>

class IMemory;

struct CpuContext {
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t P;
    uint8_t SP;
    uint16_t PC;
};

class Cpu
{
public:
    Cpu();
    void tick(CpuContext& context, IMemory& memory);
};

#endif
