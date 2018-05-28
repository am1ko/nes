#include "bus.h"
#include "memorymap.h"
#include <cassert>

// ---------------------------------------------------------------------------------------------- //
Bus::Bus(IOMemoryMapped& ram, IOMemoryMapped& rom, IOMemoryMapped& io_registers) :
    ram(ram), rom(rom), io_registers(io_registers) {
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Bus::read(uint16_t addr) {
#ifdef DEBUG_MEM
    std::cout << "RD[" << boost::format("0x%04X") % addr << "] <- ";
    std::cout << boost::format("0x%02X") % static_cast<int>(ret);
    std::cout << std::endl;
#endif
    return get_bus_device(addr).read(addr);
}

// ---------------------------------------------------------------------------------------------- //
void Bus::write(uint16_t addr, uint8_t value) {
    get_bus_device(addr).write(addr, value);
#ifdef DEBUG_MEM
    std::cout << "WR[" << boost::format("0x%04X") % addr << "] -> ";
    std::cout << boost::format("0x%02X") % static_cast<int>(value);
    std::cout << std::endl;
#endif

}

// ---------------------------------------------------------------------------------------------- //
IOMemoryMapped & Bus::get_bus_device(uint16_t addr) {
    if ((addr >= MemoryMap::RAM_START) && (addr <= MemoryMap::RAM_END)) {
        return ram;
    }
    else if ((addr >= MemoryMap::ROM_START) && (addr <= MemoryMap::ROM_END)) {
        return rom;
    }
    else if ((addr >= MemoryMap::IO_REGISTERS_START) && (addr <= MemoryMap::IO_REGISTERS_END)) {
        return io_registers;
    }

    assert(false);
}
