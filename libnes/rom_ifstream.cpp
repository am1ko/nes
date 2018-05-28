#include "rom_ifstream.h"
#include "memorymap.h"

// ---------------------------------------------------------------------------------------------- //
ROM_ifstream::ROM_ifstream(std::string& fname) : file(fname, std::ios::in | std::ios::binary) {
    if (file) {
        file.seekg (0, file.end);
        int length = file.tellg();
        file.seekg (0, file.beg);
    }
}

// ---------------------------------------------------------------------------------------------- //
ROM_ifstream::~ROM_ifstream() {
    file.close();
}

// ---------------------------------------------------------------------------------------------- //
uint8_t ROM_ifstream::read(uint16_t addr) {
    uint8_t ret = 0U;

    if (addr >= MemoryMap::ROM_UPPER_BANK_START) {
        uint16_t const offset = 16 + addr - MemoryMap::ROM_UPPER_BANK_START;

        file.seekg(offset);
        file.get((char&)ret);
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------- //
void ROM_ifstream::write(uint16_t addr, uint8_t value) {
}