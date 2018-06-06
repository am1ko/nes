#ifndef ROM_IFSTREAM_H
#define ROM_IFSTREAM_H

#include "iomemorymapped.h"
#include <string>
#include <fstream>

#define ROM_BANK_SIZE               0x4000

class ROM_ifstream : public IOMemoryMapped {
    std::ifstream file;
    size_t rom_size;
    uint8_t num_prg_rom_banks;
    uint8_t * rom;
public:
    ROM_ifstream(std::string& file, uint8_t * storage, size_t size);
    ~ROM_ifstream();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif