// ---------------------------------------------------------------------------------------------- //
// About palette:
// There is a 64-byte (8 x 8 byte) attribute table after each nametable
//    - 1 byte in attribute table corresponds to 4 x 4 tile area
//    - each byte is split into 2 bit regions for each 2 x 2 tile corner
//
// Example
//  - AT_BYTE = $E4 = 11 10 01 00
//
//   4x4 tile area (32x32 pixels)
//   +----+----+----+----+
//   | 00 | 00 | 01 | 01 |
//   +----+----+----+----+
//   | 00 | 00 | 01 | 01 |
//   +----+----+----+----+
//   | 10 | 10 | 11 | 11 |
//   +----+----+----+----+
//   | 10 | 10 | 11 | 11 |
//   +----+----+----+----+
//
//  00 => Use palette 1/4
//  01 => Use palette 2/4
//  10 => Use palette 3/4
//  11 => Use palette 4/4
//
// Images are encoded using 2 bits per pixel. These bits select which color of
// the four available ones to select from the palette that is selected
// using the scheme above
//

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
static uint8_t get_palette(uint8_t at_byte, uint8_t nt_x, uint8_t nt_y) {
    uint8_t const top_left_color = at_byte & 0x03U;
    uint8_t const top_right_color = (at_byte & 0x0CU) >> 2;
    uint8_t const bottom_left_color = (at_byte & 0x30U) >> 4;
    uint8_t const bottom_right_color = (at_byte & 0xC0U) >> 6;
    uint8_t const x_odd = (nt_x/2U) % 2U;
    uint8_t const y_odd = (nt_y/2U) % 2U;
    uint8_t palette_selection = 0U;;

    if (!x_odd and !y_odd) {
        palette_selection = top_left_color;
    }
    else if (!x_odd and y_odd) {
        palette_selection = bottom_left_color;
    }
    else if (x_odd and !y_odd) {
        palette_selection = top_right_color;
    }
    else if (x_odd and y_odd) {
        palette_selection = bottom_right_color;
    }

    return palette_selection;
}

// ---------------------------------------------------------------------------------------------- //
static uint16_t get_at_byte_addr(uint16_t nt_base_addr, uint8_t nt_x, uint8_t nt_y) {
    uint8_t const palette_x = nt_x / 4U;
    uint8_t const palette_y = nt_y / 4U;
    assert(palette_x < 8);
    assert(palette_y < 8);
    uint16_t const at_base_addr = nt_base_addr + 0x3C0U;
    return at_base_addr + palette_y*8 + palette_x;
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
                    uint16_t const nt_base_addr = 0x2000U + (registers.PPUCTRL & 0x03U) * 0x400U;
                    uint8_t const nt_byte = bus.read(nt_base_addr + row*32 + col);
                    uint8_t chr_lsb[8];        // CHR tile, 8x8 pixels, least significant bits
                    uint8_t chr_msb[8];        // CHR tile, 8x8 pixels, most significant bits
                    uint8_t const at_byte = bus.read(get_at_byte_addr(nt_base_addr, col, row));
                    uint8_t const palette_index = get_palette(at_byte, col, row);

                    for (unsigned b = 0U; b < 8U; b++) {
                        // Read the CHR
                        uint16_t const chr_rom_base_addr =
                                    ((registers.PPUCTRL & FLAG_PPUCTRL_B) >> 4)*0x1000U;
                        chr_lsb[b]  = bus.read(chr_rom_base_addr + nt_byte*16 + b);
                        chr_msb[b] = bus.read(chr_rom_base_addr + nt_byte*16 + 8 + b);
                    }

                    // Render 1 CHR
                    for (unsigned y = 0U; y < 8U; y++) {
                        for (unsigned x = 0U; x < 8U; x++) {
                            uint8_t const lsb = (chr_lsb[y] & (1 << x)) >> x;
                            uint8_t const msb = (chr_msb[y] & (1 << x)) >> x;
                            uint8_t const color_index = lsb | (msb << 1);
                            assert(palette_index < 4);
                            assert(color_index < 4);

                            uint16_t pixel_color_addr = 0x3F00U + palette_index * 4 + color_index;

                            if ((pixel_color_addr == 0x3F04U) or (pixel_color_addr == 0x3F08U) or
                                (pixel_color_addr == 0x3F0CU)) {
                                pixel_color_addr = 0x3F00U;
                            }

                            renderer.draw_pixel(col*8 + 7 - x, row*8 + y, bus.read(pixel_color_addr));
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