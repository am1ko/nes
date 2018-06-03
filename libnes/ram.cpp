#include "ram.h"
#include "memorymap.h"
#include <cstring>
#include <cassert>

RAM::RAM(uint8_t * const ram, size_t size) : ram(ram), size(size) {
    assert(size == MemoryMap::RAM_MIRROR_START);
    (void)std::memset(ram, 0U, size);
}

RAM::~RAM() {

}

// ---------------------------------------------------------------------------------------------- //
uint8_t RAM::read(uint16_t addr) {
    assert(addr >= MemoryMap::RAM_START);
    assert(addr <= MemoryMap::RAM_END);

    if (addr >= MemoryMap::RAM_MIRROR_START) {
        addr -= MemoryMap::RAM_MIRROR_START - MemoryMap::RAM_START;
    }

    return ram[addr - MemoryMap::RAM_START];
}

// ---------------------------------------------------------------------------------------------- //
void RAM::write(uint16_t addr, uint8_t value) {
    assert(addr >= MemoryMap::RAM_START);
    assert(addr <= MemoryMap::RAM_END);

    if (addr >= MemoryMap::RAM_MIRROR_START) {
        addr -= MemoryMap::RAM_MIRROR_START - MemoryMap::RAM_START;
    }

    ram[addr - MemoryMap::RAM_START] = value;
}