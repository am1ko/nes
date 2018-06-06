#include "ppu.h"
#include <cstring>

Ppu::Ppu() {
    cpu_irq = NULL;
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::reset() {
    (void)std::memset(&registers, 0U, sizeof(registers));
    scan_line = 0U;
    cycle = 0U;
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::process_cycle() {
    if ((scan_line == 241U) && (cycle == 1U)) {
        registers.PPUSTATUS |= 0x80U;
        if (cpu_irq) {
            cpu_irq->set_interrupt_pending(CpuInterrupt::InterruptSource::NMI);
        }
    }
    else if ((scan_line == (SCAN_LINES_PER_FRAME - 1U)) && (cycle == 1U)) {
        registers.PPUSTATUS &= ~0x80U;
    }
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::set_interrupt_handler(CpuInterrupt* cpu_irq) {
    this->cpu_irq = cpu_irq;
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
    if (addr == ADDR_PPUSTATUS) {
        uint8_t const ret = registers.PPUSTATUS;
        registers.PPUSTATUS &= ~0x80U;
        return ret;
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::write(uint16_t addr, uint8_t value) {
}
