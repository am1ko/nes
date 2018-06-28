#ifndef RAM_H
#define RAM_H

#include <cassert>
#include <array>
#include <cstdint>
#include "iomemorymapped.h"

template <std::size_t N>
class RAM : public IOMemoryMapped {
    std::array<uint8_t, N>& ram;
public:
    RAM(std::array<uint8_t, N>& ram);
    ~RAM();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

// ---------------------------------------------------------------------------------------------- //
template <std::size_t N>
RAM<N>::RAM(std::array<uint8_t, N>& ram) : ram(ram) {

}

// ---------------------------------------------------------------------------------------------- //
template <std::size_t N>
RAM<N>::~RAM() {

}

// ---------------------------------------------------------------------------------------------- //
template <std::size_t N>
uint8_t RAM<N>::read(uint16_t addr) {
    assert(addr < ram.size());
    return ram[addr];
}

// ---------------------------------------------------------------------------------------------- //
template <std::size_t N>
void RAM<N>::write(uint16_t addr, uint8_t value) {
    assert(addr < ram.size());
    ram[addr] = value;
}

#endif
