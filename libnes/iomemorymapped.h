
#ifndef IOMEMORYMAPPED_H
#define IOMEMORYMAPPED_H

#include <cstdint>

class IOMemoryMapped
{
public:
    virtual uint8_t read(uint16_t addr) = 0;
    virtual void write(uint16_t addr, uint8_t value) = 0;
};

#endif
