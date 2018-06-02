#ifndef ROM_IFSTREAM_H
#define ROM_IFSTREAM_H

#include "iomemorymapped.h"
#include <string>
#include <fstream>

class ROM_ifstream : public IOMemoryMapped {
    std::ifstream file;
    size_t file_size;
    uint8_t num_prg_rom_banks;
public:
    explicit ROM_ifstream(std::string& file);
    ~ROM_ifstream();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

#endif