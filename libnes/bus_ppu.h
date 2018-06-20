#ifndef BUS_PPU_H
#define BUS_PPU_H

#include <cstdint>
#include "iomemorymapped.h"

class BusPpu : public IOMemoryMapped
{
    IOMemoryMapped & vram;
    IOMemoryMapped & pal_ram;
    IOMemoryMapped & chr_rom;
public:
// ---------------------------------------------------------------------------------------------- //
    BusPpu(IOMemoryMapped& vram, IOMemoryMapped& pal_ram, IOMemoryMapped & chr_rom);
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif
