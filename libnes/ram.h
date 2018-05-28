#ifndef RAM_H
#define RAM_H

#include <cstdint>
#include "iomemorymapped.h"

class RAM : public IOMemoryMapped {
    uint8_t ram[0x800U];    // 2 kB internal RAM
public:
    explicit RAM();
    ~RAM();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif
