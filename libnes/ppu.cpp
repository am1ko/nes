#include "ppu.h"
#include <cstring>

// ---------------------------------------------------------------------------------------------- //
void Ppu::reset() {
    (void)std::memset(&registers, 0U, sizeof(registers));
    scan_line = 0U;
    cycle = 0U;
}

// ---------------------------------------------------------------------------------------------- //
bool Ppu::process_cycle() {
    bool ret = false;
    if ((scan_line == 241U) && (cycle == 1U)) {
        registers.PPUSTATUS |= 0x80U;
        ret = true;
    }
    else if ((scan_line == (SCAN_LINES_PER_FRAME - 1U)) && (cycle == 1U)) {
        registers.PPUSTATUS &= ~0x80U;
    }
    return ret;
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
bool Ppu::tick() {
    bool const vblank_irq = process_cycle();
    advance_cycle();
    return vblank_irq;
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
