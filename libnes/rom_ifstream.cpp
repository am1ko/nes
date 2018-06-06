#include "rom_ifstream.h"
#include "memorymap.h"
#include <cassert>

#define INES_HEADER_SIZE            16
#define INES_NUM_PRG_ROM_OFFSET     4

// ---------------------------------------------------------------------------------------------- //
ROM_ifstream::ROM_ifstream(std::string& fname, uint8_t * storage, size_t size)  :
                                                    file(fname, std::ios::in | std::ios::binary) {
    assert(storage != NULL);
    assert(size >= ROM_BANK_SIZE);

    if (file) {
        file.seekg (0, file.end);
        size_t const file_size = file.tellg();
        file.seekg (0, file.beg);
        assert(file_size > INES_HEADER_SIZE);

        char ines_header[INES_HEADER_SIZE];
        file.get(ines_header, INES_HEADER_SIZE);

        num_prg_rom_banks = (uint8_t)ines_header[INES_NUM_PRG_ROM_OFFSET];

        assert(num_prg_rom_banks < 3);

        rom_size = num_prg_rom_banks*ROM_BANK_SIZE;

        assert(file_size >= rom_size + INES_HEADER_SIZE);
        assert(size >= rom_size);

        rom = storage;
        file.seekg(INES_HEADER_SIZE);
        file.read((char*)rom, rom_size);
        file.close();
    }
}

// ---------------------------------------------------------------------------------------------- //
ROM_ifstream::~ROM_ifstream() {
}

// ---------------------------------------------------------------------------------------------- //
uint8_t ROM_ifstream::read(uint16_t addr) {
    uint8_t ret = 0U;

    assert(addr >= MemoryMap::ROM_START && addr <= MemoryMap::ROM_END);

    if (addr >= MemoryMap::ROM_START) {
        uint16_t offset = 0xFFFFU;

        if (num_prg_rom_banks == 1U) {
            if (addr >= MemoryMap::ROM_UPPER_BANK_START) addr -= ROM_BANK_SIZE;
        }

        offset = addr - MemoryMap::ROM_START;

        assert(offset < rom_size);

        ret = rom[offset];
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------- //
void ROM_ifstream::write(uint16_t addr, uint8_t value) {
}