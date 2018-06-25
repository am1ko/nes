#include "bus.h"
#include "memorymap.h"
#include <cassert>

// #define DEBUG_MEM

#ifdef DEBUG_MEM
#include <iostream>
#include <boost/format.hpp>
#endif

// ---------------------------------------------------------------------------------------------- //
Bus::Bus(IOMemoryMapped& ram, IOMemoryMapped& prg_rom_lower,IOMemoryMapped& prg_rom_upper,
         IOMemoryMapped& ppu, IOMemoryMapped& apu) :
    ram(ram), prg_rom_lower(prg_rom_lower), prg_rom_upper(prg_rom_upper),ppu(ppu), apu(apu) {
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Bus::read(uint16_t addr) {
    uint16_t offset = 0U;
    uint8_t const ret = get_bus_device(addr, offset).read(addr - offset);
#ifdef DEBUG_MEM
    std::cout << "RD[" << boost::format("0x%04X") % addr << "] <- ";
    std::cout << boost::format("0x%02X") % static_cast<int>(ret);
    std::cout << std::endl;
#endif
    return ret;
}

// ---------------------------------------------------------------------------------------------- //
void Bus::write(uint16_t addr, uint8_t value) {
    if (addr == MemoryMap::OAM_DMA) {
        for (int i = 0; i < 256; i++) {
            ppu.write(0x2004U, ram.read((value << 8) + i));
        }
        // TODO(amiko): This should take 513 or 514 CPU cycles. Could return the cycle value from
        //              here?
    }
    else {
        uint16_t offset = 0U;
        get_bus_device(addr, offset).write(addr - offset, value);
    }
#ifdef DEBUG_MEM
    std::cout << "WR[" << boost::format("0x%04X") % addr << "] -> ";
    std::cout << boost::format("0x%02X") % static_cast<int>(value);
    std::cout << std::endl;
#endif

}

// ---------------------------------------------------------------------------------------------- //
IOMemoryMapped & Bus::get_bus_device(uint16_t addr, uint16_t & offset) {
    if ((addr >= MemoryMap::RAM_START) && (addr <= MemoryMap::RAM_END)) {
        offset = MemoryMap::RAM_START;
        return ram;
    }
    else if ((addr >= MemoryMap::ROM_LOWER_BANK_START) and (addr <= MemoryMap::ROM_LOWER_BANK_END)){
        offset = MemoryMap::ROM_LOWER_BANK_START;
        return prg_rom_lower;
    }
    else if ((addr >= MemoryMap::ROM_UPPER_BANK_START) and (addr <= MemoryMap::ROM_UPPER_BANK_END)){
        offset = MemoryMap::ROM_UPPER_BANK_START;
        return prg_rom_upper;
    }
    else if ((addr >= MemoryMap::PPU_START) and (addr <= MemoryMap::PPU_END)) {
        offset = 0U;
        return ppu;
    }
    else {
        return apu;
    }

    assert(false);
}
