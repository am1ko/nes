// #define DEBUG_MEM
#include "memory.h"
#ifdef DEBUG_MEM
#include <iostream>
#endif

// ---------------------------------------------------------------------------------------------- //
Memory::Memory(std::string& fname) : file(fname, std::ios::in | std::ios::binary) {
    if (file) {
        // get length of file:
        file.seekg (0, file.end);
        int length = file.tellg();
        file.seekg (0, file.beg);
        // std::cout << "rom size " << std::hex << length << std::endl;
    }
}

// ---------------------------------------------------------------------------------------------- //
Memory::~Memory() {
    file.close();
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Memory::read(uint16_t addr) {
    uint8_t ret = 0U;
#ifdef DEBUG_MEM
    std::cout << "read from " << std::hex << addr;
#endif

    if (addr <= 0x2000U) {
        // ram address
        if (addr >= 0x800U) {
            addr -= 0x800U;     // mirrored region
        }

        ret = ram[addr];
    }
    else if (addr >= 0xC000U) {
        uint16_t const offset = 16 + addr - 0xC000U;

        file.seekg(offset);
        file.get((char&)ret);

#ifdef DEBUG_MEM
        std::cout << " file offset " << offset;
#endif
    }

#ifdef DEBUG_MEM
    std::cout << " return " << std::hex << static_cast<int>(ret) << std::endl;
#endif

    return ret;
}

// ---------------------------------------------------------------------------------------------- //
void Memory::write(uint16_t addr, uint8_t value) {
    if (addr < 0x2000U) {
        // ram address
        if (addr >= 0x800U) {
            addr -= 0x800U;     // mirrored region
        }

        ram[addr] = value;
    }

#ifdef DEBUG_MEM
    std::cout << "write " << std::hex << static_cast<int>(value) << " to " << std::hex
              << addr << std::endl;
#endif
}