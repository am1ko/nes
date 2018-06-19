#ifndef ROM_H
#define ROM_H

#include <array>
#include <cstdint>
#include "iomemorymapped.h"

template <std::size_t N>
class ROM : public IOMemoryMapped {
    std::array<uint8_t, N>& rom;
public:
    ROM(std::array<uint8_t, N>& rom);
    ~ROM();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};

// ---------------------------------------------------------------------------------------------- //
template <std::size_t N>
ROM<N>::ROM(std::array<uint8_t, N>& rom) : rom(rom) {

}

// ---------------------------------------------------------------------------------------------- //
template <std::size_t N>
ROM<N>::~ROM() {

}

// ---------------------------------------------------------------------------------------------- //
template <std::size_t N>
uint8_t ROM<N>::read(uint16_t addr) {
    assert(addr < rom.size());
    return rom[addr];
}

// ---------------------------------------------------------------------------------------------- //
template <std::size_t N>
void ROM<N>::write(uint16_t addr, uint8_t value) {
    assert(false);
}

#endif
