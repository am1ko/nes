#ifndef PPU_H
#define PPU_H

#include <array>
#include "cpu_interrupt.h"
#include "iomemorymapped.h"
#include "renderer.h"

class Ppu : public IOMemoryMapped
{
    IOMemoryMapped& bus;
    IOMemoryMapped& oam;
    Renderer& renderer;

    unsigned scan_line = 0U;
    unsigned cycle = 0U;

    enum PPUADDR_state {
        WAITING_FOR_MSB,
        WAITING_FOR_LSB
    };
    enum PPUADDR_state ppuaddr_state = WAITING_FOR_MSB;

    struct Registers {
        uint8_t PPUCTRL;
        uint8_t PPUMASK;
        uint8_t PPUSTATUS;
        uint8_t OAMADDR;
        uint8_t PPUSCROLL;
        uint16_t PPUADDR;
        uint8_t PPUDATA;
    };

    bool process_cycle();
    void advance_cycle();
    uint8_t get_address_increment() const;

    void load_tile(uint16_t ptable_addr, uint8_t tile_index, std::array<uint8_t, 8>& msb,
                   std::array<uint8_t, 8>& lsb);
    void draw_tile(uint8_t palette_index, uint8_t x_pos, uint8_t y_pos, bool flip_vertical,
                    bool flip_horizontal,
                    std::array<uint8_t, 8>& tile_msb, std::array<uint8_t, 8>& tile_lsb);
    void render();

public:
    static const uint16_t SCAN_LINES_PER_FRAME = 262U;
    static const uint16_t CYCLES_PER_SCAN_LINE = 341U;

    static const uint16_t ADDR_PPUCTRL    = 0x2000U;
    static const uint16_t ADDR_PPUMASK    = 0x2001U;
    static const uint16_t ADDR_PPUSTATUS  = 0x2002U;
    static const uint16_t ADDR_OAMADDR    = 0x2003U;
    static const uint16_t ADDR_OAMDATA    = 0x2004U;
    static const uint16_t ADDR_PPUSCROLL  = 0x2005U;
    static const uint16_t ADDR_PPUADDR    = 0x2006U;
    static const uint16_t ADDR_PPUDATA    = 0x2007U;

    static const uint8_t FLAG_PPUCTRL_V   = (1U << 7);
    static const uint8_t FLAG_PPUCTRL_P   = (1U << 6);
    static const uint8_t FLAG_PPUCTRL_H   = (1U << 5);
    static const uint8_t FLAG_PPUCTRL_B   = (1U << 4);
    static const uint8_t FLAG_PPUCTRL_S   = (1U << 3);
    static const uint8_t FLAG_PPUCTRL_I   = (1U << 2);
    static const uint8_t FLAG_PPUCTRL_N   = (1U << 0);

    static const uint8_t FLAG_PPUSTATUS_V = (1U << 7);
    static const uint8_t FLAG_PPUSTATUS_S = (1U << 6);
    static const uint8_t FLAG_PPUSTATUS_O = (1U << 5);

    Registers registers = {0};

    Ppu(IOMemoryMapped& bus, IOMemoryMapped& oam, Renderer& renderer);
    virtual ~Ppu();

    void reset();
    bool tick();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif