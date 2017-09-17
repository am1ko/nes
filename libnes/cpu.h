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
    IMemory & memory;
    uint16_t get_cc01_param_addr(uint8_t addr_mode);
    uint16_t adc(uint8_t instr);
    void update_flags(uint16_t result);;
public:
    CpuContext context;
    Cpu(IMemory& memory);
    void reset();
    void tick();
};

#endif
