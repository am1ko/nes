#include "ppu.h"
#include <cstring>

Ppu::Ppu(CpuInterrupt& cpu_irq) : cpu_irq(cpu_irq) {
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::reset() {
    (void)std::memset(&context, 0U, sizeof(context));
    scan_line = 0U;
    cycle = 0U;
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::process_cycle() {
    if ((scan_line == 241U) && (cycle == 1U)) {
        context.PPUSTATUS |= 0x80U;
        cpu_irq.set_interrupt_pending(CpuInterrupt::InterruptSource::NMI);
    }
    else if ((scan_line == (SCAN_LINES_PER_FRAME - 1U)) && (cycle == 1U)) {
        context.PPUSTATUS &= ~0x80U;
    }
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::advance_cycle() {
    cycle++;
    if (cycle == CYCLES_PER_SCAN_LINE) {
        cycle = 0U;
        scan_line++;

        if (scan_line == SCAN_LINES_PER_FRAME) { scan_line = 0U; }
    };
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::tick() {
    process_cycle();
    advance_cycle();
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Ppu::read(uint16_t addr) {
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::write(uint16_t addr, uint8_t value) {
}
