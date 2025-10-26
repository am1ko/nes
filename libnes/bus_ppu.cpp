#include "bus_ppu.h"
#include "memorymap.h"
#include <cassert>

// #define DEBUG_MEM

#ifdef DEBUG_MEM
#include <iostream>
#include <boost/format.hpp>
#endif

// ---------------------------------------------------------------------------------------------- //
static uint16_t convert_palette_ram_addr(uint16_t addr) {
    if ((addr == 0x3F10U) or (addr == 0x3F14U) or (addr == 0x3F18U) or (addr == 0x3F1CU)) {
        addr -= 0x10U;
    }
    return addr;
}

// ---------------------------------------------------------------------------------------------- //
BusPpu::BusPpu(IOMemoryMapped& vram, IOMemoryMapped& pal_ram, IOMemoryMapped & chr_rom)
        : vram(vram), pal_ram(pal_ram), chr_rom(chr_rom) {
}

// ---------------------------------------------------------------------------------------------- //
BusPpu::~BusPpu() {
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
    else if (addr >= 0x2000U and addr < 0x2800U) {
        ret = vram.read(addr - 0x2000U);
    }
    else if ((addr >= 0x3F00U) and (addr < 0x3F20U)) {
        ret = pal_ram.read(convert_palette_ram_addr(addr) - 0x3F00U);
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
    if (addr >= 0x2000U and addr < 0x2800U) {
        vram.write(addr - 0x2000U, value);
    }
    else if ((addr >= 0x3F00) and (addr < 0x3F20)) {
        pal_ram.write(convert_palette_ram_addr(addr) - 0x3F00U, value);
    }

}
