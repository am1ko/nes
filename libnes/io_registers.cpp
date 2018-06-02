
#include "io_registers.h"
#include "memorymap.h"
#include <cstring>
#include <cassert>

IO_Registers::IO_Registers() {
}

IO_Registers::~IO_Registers() {

}

// ---------------------------------------------------------------------------------------------- //
uint8_t IO_Registers::read(uint16_t addr) {
    if (addr == 0x2002) return 0x80U;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
void IO_Registers::write(uint16_t addr, uint8_t value) {

}