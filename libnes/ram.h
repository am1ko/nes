#ifndef RAM_H
#define RAM_H

#include <cstdint>
#include <string>
#include "iomemorymapped.h"

class RAM : public IOMemoryMapped {
    uint8_t * const ram;
    size_t size;
public:
    explicit RAM(uint8_t * const ram, size_t size);
    ~RAM();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif
