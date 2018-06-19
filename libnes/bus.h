#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include "iomemorymapped.h"

class Bus : public IOMemoryMapped
{
    IOMemoryMapped & ram;
    IOMemoryMapped & prg_rom_lower;
    IOMemoryMapped & prg_rom_upper;
    IOMemoryMapped & ppu;
    IOMemoryMapped & apu;

    IOMemoryMapped & get_bus_device(uint16_t addr, uint16_t & offset);
public:
// ---------------------------------------------------------------------------------------------- //
    Bus(IOMemoryMapped& ram, IOMemoryMapped& prg_rom_lower,IOMemoryMapped& prg_rom_upper,
        IOMemoryMapped& ppu, IOMemoryMapped& apu);
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif
