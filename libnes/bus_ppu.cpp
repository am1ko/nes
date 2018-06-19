#include "bus_ppu.h"
#include "memorymap.h"
#include <cassert>

// #define DEBUG_MEM

#ifdef DEBUG_MEM
#include <iostream>
#include <boost/format.hpp>
#endif

// ---------------------------------------------------------------------------------------------- //
BusPpu::BusPpu(IOMemoryMapped& vram, IOMemoryMapped & chr_rom) : vram(vram), chr_rom(chr_rom) {
}

// ---------------------------------------------------------------------------------------------- //
uint8_t BusPpu::read(uint16_t addr) {
    uint8_t ret = 0U;
#ifdef DEBUG_MEM
    std::cout << "RD[" << boost::format("0x%04X") % addr << "] <- ";
    std::cout << boost::format("0x%02X") % static_cast<int>(ret);
    std::cout << std::endl;
#endif
    if (addr < 0x2000U) {
        ret = chr_rom.read(addr);
    }
    if (addr >= 0x2000U and addr < 0x3000U) {
        ret = vram.read(addr - 0x2000U);
    }
    return ret;
}

// ---------------------------------------------------------------------------------------------- //
void BusPpu::write(uint16_t addr, uint8_t value) {
#ifdef DEBUG_MEM
    std::cout << "WR[" << boost::format("0x%04X") % addr << "] -> ";
    std::cout << boost::format("0x%02X") % static_cast<int>(value);
    std::cout << std::endl;
#endif
    if (addr >= 0x2000U and addr < 0x3000U) {
        vram.write(addr - 0x2000U, value);
    }

}
