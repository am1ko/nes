#include "bus_ppu.h"
#include "memorymap.h"
#include <cassert>

// ---------------------------------------------------------------------------------------------- //
BusPpu::BusPpu(IOMemoryMapped& vram, IOMemoryMapped& chr_rom) :
    vram(vram), chr_rom(chr_rom) {
}

// ---------------------------------------------------------------------------------------------- //
uint8_t BusPpu::read(uint16_t addr) {
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
void BusPpu::write(uint16_t addr, uint8_t value) {

}
