#include "io_registers.h"
#include "memorymap.h"
#include <cstring>
#include <cassert>

IO_Registers::IO_Registers()
    : joy_state{0U, 0U}, joy_shift{0U, 0U}, strobe(false) {
}

IO_Registers::~IO_Registers() {
}

// ---------------------------------------------------------------------------------------------- //
uint8_t IO_Registers::read(uint16_t addr) {
    int i = (addr == MemoryMap::IO_JOY1) ? 0 : 1;
    uint8_t ret = 0U;
    if (strobe) {
        ret = joy_state[i] & 0x01U;
    } else {
        ret = joy_shift[i] & 0x01U;
        joy_shift[i] >>= 1;
    }
    return ret | 0x40U;
}

// ---------------------------------------------------------------------------------------------- //
void IO_Registers::write(uint16_t addr, uint8_t value) {
    if (addr == MemoryMap::IO_JOY1) {
        strobe = (value & 0x01U) == 0x01U;
        if (strobe) {
            joy_shift[0] = joy_state[0];
            joy_shift[1] = joy_state[1];
        }
    }
}

// ---------------------------------------------------------------------------------------------- //
void IO_Registers::set_button(uint8_t joy, buttons button) {
    joy_state[joy] |= button;
}

// ---------------------------------------------------------------------------------------------- //
void IO_Registers::clear_button(uint8_t joy, buttons button) {
    joy_state[joy] &= ~button;
}

// ---------------------------------------------------------------------------------------------- //
void IO_Registers::clear_buttons() {
    joy_state[0] = 0U;
    joy_state[1] = 0U;
}