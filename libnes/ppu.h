#ifndef PPU_H
#define PPU_H

#include "cpu_interrupt.h"
#include "iomemorymapped.h"

class Ppu : public IOMemoryMapped
{
    unsigned scan_line;
    unsigned cycle;
    CpuInterrupt& cpu_irq;

    void process_cycle();
    void advance_cycle();

public:
    struct Registers {
        uint8_t PPUCTRL;
        uint8_t PPUMASK;
        uint8_t PPUSTATUS;
        uint8_t OAMADDR;
        uint8_t PPUSCROLL;
        uint8_t PPUADDR;
        uint8_t PPUDATA;
    };

    static const uint16_t SCAN_LINES_PER_FRAME = 262U;
    static const uint16_t CYCLES_PER_SCAN_LINE = 341U;

    static const uint16_t ADDR_PPUCTRL   = 0x2000U;
    static const uint16_t ADDR_PPUMASK   = 0x2001U;
    static const uint16_t ADDR_PPUSTATUS = 0x2002U;
    static const uint16_t ADDR_OAMADDR   = 0x2003U;
    static const uint16_t ADDR_PPUSCROLL = 0x2004U;
    static const uint16_t ADDR_PPUADDR   = 0x2005U;
    static const uint16_t ADDR_PPUDATA   = 0x2006U;

    Registers registers;

    Ppu(CpuInterrupt& cpu_irq);
    void reset();
    void tick();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif