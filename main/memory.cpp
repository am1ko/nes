// #define DEBUG_MEM
#include "memory.h"
#ifdef DEBUG_MEM
#include <iostream>
#include <boost/format.hpp>
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
    }

#ifdef DEBUG_MEM
    std::cout << "RD[" << boost::format("0x%04X") % addr << "] <- ";
    std::cout << boost::format("0x%02X") % static_cast<int>(ret);
    std::cout << std::endl;
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
    std::cout << "WR[" << boost::format("0x%04X") % addr << "] -> ";
    std::cout << boost::format("0x%02X") % static_cast<int>(value);
    std::cout << std::endl;
#endif
}