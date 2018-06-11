#include "ram.h"
#include "memorymap.h"
#include <cstring>
#include <cassert>

// ---------------------------------------------------------------------------------------------- //
RAM::RAM(uint8_t * const ram, size_t size) : ram(ram), size(size) {
    assert(size > 0);
    (void)std::memset(ram, 0U, size);
}

// ---------------------------------------------------------------------------------------------- //
RAM::~RAM() {

}

// ---------------------------------------------------------------------------------------------- //
uint8_t RAM::read(uint16_t addr) {
    assert(addr < size);
    return ram[addr];
}

// ---------------------------------------------------------------------------------------------- //
void RAM::write(uint16_t addr, uint8_t value) {
    assert(addr < size);
    ram[addr] = value;
}