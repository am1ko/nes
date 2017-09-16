#ifndef CPU_H
#define CPU_H

#include <cstdbool>
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
    CpuContext context;
    Cpu();
    void reset(IMemory& memory);
    void tick(IMemory& memory);
};

#endif
