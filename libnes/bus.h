#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include "iomemorymapped.h"

class Bus : public IOMemoryMapped
{
    IOMemoryMapped & ram;
    IOMemoryMapped & rom;
    IOMemoryMapped & ppu;

    IOMemoryMapped & get_bus_device(uint16_t addr);
public:
    Bus(IOMemoryMapped& ram, IOMemoryMapped& rom, IOMemoryMapped& ppu);
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif
