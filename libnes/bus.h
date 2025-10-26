#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include "iomemorymapped.h"

// ---------------------------------------------------------------------------------------------- //
class IBusLogger {
public:
    virtual void log_read(uint16_t addr, uint8_t value);
    virtual void log_write(uint16_t addr, uint8_t value);
};

// ---------------------------------------------------------------------------------------------- //
class Bus : public IOMemoryMapped
{
    IOMemoryMapped & ram;
    IOMemoryMapped & prg_rom_lower;
    IOMemoryMapped & prg_rom_upper;
    IOMemoryMapped & ppu;
    IOMemoryMapped & apu;

    IOMemoryMapped & get_bus_device(uint16_t addr, uint16_t & offset);
    IBusLogger * logger;
public:
// ---------------------------------------------------------------------------------------------- //
    Bus(IOMemoryMapped& ram, IOMemoryMapped& prg_rom_lower,IOMemoryMapped& prg_rom_upper,
        IOMemoryMapped& ppu, IOMemoryMapped& apu);
    virtual ~Bus();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
    void set_logger(IBusLogger * logger);
};

#endif
