#include "emu.h"

Emu::Emu(Cpu& cpu, Ppu& ppu) : cpu(cpu), ppu(ppu) {}

// ---------------------------------------------------------------------------------------------- //
void Emu::reset() {
    cpu.reset();
    ppu.reset();
}

// ---------------------------------------------------------------------------------------------- //
unsigned Emu::tick() {
    unsigned const ret = cpu.tick();

    for (unsigned i = 0U; i < ret*3U; i++) {
        bool const irq = ppu.tick();
        if (irq) {
            cpu.set_interrupt_pending(CpuInterrupt::InterruptSource::NMI);
        }
    }

    return ret;
}
