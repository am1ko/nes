#ifndef EMU_H
#define EMU_H

#include "cpu.h"
#include "ppu.h"

struct Emu {
    Emu(Cpu& cpu, Ppu& ppu);
    void reset();
    unsigned tick();
private:
    Cpu& cpu;
    Ppu& ppu;
};

#endif
