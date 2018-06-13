#ifndef PPU_H
#define PPU_H

#include "cpu_interrupt.h"
#include "iomemorymapped.h"

class Ppu : public IOMemoryMapped
{
    IOMemoryMapped& bus;

    unsigned scan_line;
    unsigned cycle;
    uint16_t vram_address;


    enum PPUADDR_state {
        WAITING_FOR_MSB,
        WAITING_FOR_LSB
    };
    enum PPUADDR_state ppuaddr_state;

    struct Registers {
        uint8_t PPUCTRL;
        uint8_t PPUMASK;
        uint8_t PPUSTATUS;
        uint8_t OAMADDR;
        uint8_t PPUSCROLL;
        uint8_t PPUADDR;
        uint8_t PPUDATA;
    };

    bool process_cycle();
    void advance_cycle();

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

    Registers registers;

    Ppu(IOMemoryMapped& bus);

    void reset();
    bool tick();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif