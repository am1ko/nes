#include "rom_ifstream.h"
#include "memorymap.h"
#include <cassert>

#define ROM_BANK_SIZE               0x4000
#define INES_HEADER_SIZE            16
#define INES_NUM_PRG_ROM_OFFSET     4

// ---------------------------------------------------------------------------------------------- //
ROM_ifstream::ROM_ifstream(std::string& fname) : file(fname, std::ios::in | std::ios::binary) {
    if (file) {
        file.seekg (0, file.end);
        file_size = file.tellg();
        file.seekg (0, file.beg);

        assert(file_size > INES_HEADER_SIZE);

        char ines_header[INES_HEADER_SIZE];
        file.get(ines_header, INES_HEADER_SIZE);

        num_prg_rom_banks = (uint8_t)ines_header[INES_NUM_PRG_ROM_OFFSET];
    }
}

// ---------------------------------------------------------------------------------------------- //
ROM_ifstream::~ROM_ifstream() {
    file.close();
}

// ---------------------------------------------------------------------------------------------- //
uint8_t ROM_ifstream::read(uint16_t addr) {
    uint8_t ret = 0U;

    assert(addr >= MemoryMap::ROM_START && addr <= MemoryMap::ROM_END);

    if (addr >= MemoryMap::ROM_START) {
        uint16_t file_offset = 0xFFFFU;

        if (num_prg_rom_banks == 1U) {
            if (addr >= MemoryMap::ROM_UPPER_BANK_START) addr -= ROM_BANK_SIZE;
        }

        file_offset = INES_HEADER_SIZE + (addr - MemoryMap::ROM_START);

        assert(file_offset < file_size);

        file.seekg(file_offset);
        file.get((char&)ret);
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------- //
void ROM_ifstream::write(uint16_t addr, uint8_t value) {
}