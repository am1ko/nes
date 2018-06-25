#include "ppu.h"
#include <cstring>

// ---------------------------------------------------------------------------------------------- //
Ppu::Ppu(IOMemoryMapped& bus, IOMemoryMapped& oam) : bus(bus), oam(oam) {
}

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
        registers.PPUSTATUS |= FLAG_PPUSTATUS_V;
        if (registers.PPUCTRL & FLAG_PPUCTRL_V) {ret = true;}  // <-- generate NMI interrupt
    }
    else if ((scan_line == (SCAN_LINES_PER_FRAME - 1U)) && (cycle == 1U)) {
        registers.PPUSTATUS &= ~FLAG_PPUSTATUS_V;
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
    uint8_t ret;

    switch (addr) {
        case ADDR_OAMDATA:
            ret = oam.read(registers.OAMADDR);
        break;
        case ADDR_PPUSTATUS:
            ret = registers.PPUSTATUS;
            registers.PPUSTATUS &= ~FLAG_PPUSTATUS_V;
        break;
        case ADDR_PPUDATA:
            ret = bus.read(registers.PPUADDR);
            registers.PPUADDR += get_address_increment();;
        break;
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------- //
void Ppu::write(uint16_t addr, uint8_t value) {
    switch (addr) {
        case ADDR_PPUCTRL:
            registers.PPUCTRL = value;
        break;
        case ADDR_OAMADDR:
            registers.OAMADDR = value;
        break;
        case ADDR_OAMDATA:
            oam.write(registers.OAMADDR, value);
            registers.OAMADDR++;
        break;
        case ADDR_PPUDATA:
            bus.write(registers.PPUADDR, value);
            registers.PPUADDR += get_address_increment();;
        break;
        case ADDR_PPUADDR:
            if (ppuaddr_state == WAITING_FOR_MSB) {
                registers.PPUADDR = (value << 8);
                ppuaddr_state = WAITING_FOR_LSB;
            }
            else {
                registers.PPUADDR += value;
                ppuaddr_state = WAITING_FOR_MSB;
            }
        break;
    }
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Ppu::get_address_increment() const {
    return (registers.PPUCTRL & FLAG_PPUCTRL_I) ? 32U : 1U;
}