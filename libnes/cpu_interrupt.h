
#ifndef CPU_INTERRUPT_H
#define CPU_INTERRUPT_H

#include <cstdint>

class CpuInterrupt
{
public:
    enum InterruptSource {
        RESET,
        NMI,
        IRQ
    };
    virtual void set_interrupt_pending(enum InterruptSource source) = 0;
};

#endif
