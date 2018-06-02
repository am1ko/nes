#ifndef IO_REGISTERS_H
#define IO_REGISTERS_H

#include <cstdint>
#include "iomemorymapped.h"

class IO_Registers : public IOMemoryMapped {
public:
    explicit IO_Registers();
    ~IO_Registers();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif
