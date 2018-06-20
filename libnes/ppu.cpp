#include "ppu.h"
#include <cstring>
#include <cassert>

// ---------------------------------------------------------------------------------------------- //
Ppu::Ppu(IOMemoryMapped& bus, IOMemoryMapped& oam, Renderer& renderer) :
                                                            bus(bus), oam(oam), renderer(renderer) {
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
        if (registers.PPUCTRL & FLAG_PPUCTRL_V) {
            ret = true;   // <-- generate NMI interrupt

            // --- RENDER NAMETABLE ------------------------------------------------------------- //
            for (unsigned row = 0U; row < 30U; row++) {
                for (unsigned col = 0U; col < 32U; col++) {
                    // 8x8 bits per nametable byte
                    uint8_t const nt_byte = bus.read(0x2000 + row*32 + col);
                    uint8_t low_bits[8];
                    uint8_t high_bits[8];

                    // About palette:
                    // There is a 64-byte (8 x 8 byte) attribute table after each nametable
                    //    - 1 byte in attribute table corresponds to 4 x 4 tile area
                    //    - each byte is split into 2 bit regions for each 2 x 2 tile corner
                    unsigned const palette_x = col / 4U;
                    unsigned const palette_y = row / 4U;
                    assert(palette_x < 8);
                    assert(palette_y < 8);
                    // TODO(amiko): need to check which NT in use here
                    uint8_t const at_byte = bus.read(0x23C0 + palette_y*8 + palette_x);

                    uint8_t const top_left_color = at_byte & 0x03U;
                    uint8_t const top_right_color = (at_byte & 0x0CU) >> 2;
                    uint8_t const bottom_left_color = (at_byte & 0x30U) >> 4;
                    uint8_t const bottom_right_color = (at_byte & 0xC0U) >> 6;

                    uint8_t const x_odd = (col/2U) % 2U;
                    uint8_t const y_odd = (row/2U) % 2U;

                    uint8_t palette_selection;

                    if (x_odd and y_odd) {
                        palette_selection = top_left_color;
                    }
                    else if (x_odd and !y_odd) {
                        palette_selection = bottom_left_color;
                    }
                    else if (!x_odd and y_odd) {
                        palette_selection = top_right_color;
                    }
                    else if (!x_odd and !y_odd) {
                        palette_selection = bottom_right_color;
                    }

                    for (unsigned b = 0U; b < 8U; b++) {
                        // Read the CHR
                        // TODO(amiko): need to check which CHR ROM in use here
                        low_bits[b]  = bus.read(0x1000 + nt_byte*16 + b);
                        high_bits[b] = bus.read(0x1000 + nt_byte*16 + 8 + b);
                    }

                    // Render 1 CHR
                    for (unsigned y = 0U; y < 8U; y++) {
                        for (unsigned x = 0U; x < 8U; x++) {
                            uint8_t const lsb = (low_bits[y] & (1 << x)) >> x;
                            uint8_t const msb = (high_bits[y] & (1 << x)) >> x;
                            uint8_t const palette_index = lsb | (msb << 1);

                            renderer.draw_pixel(col*8 + 7 - x,
                                                row*8 + y,
                                                bus.read(0x3F00U
                                                        + palette_selection*4
                                                        + palette_index));
                        }
                    }

                }
            }
            renderer.flush();
            // --- RENDER NAMETABLE ------------------------------------------------------------- //

        }
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