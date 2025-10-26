#ifndef IO_REGISTERS_H
#define IO_REGISTERS_H

#include <cstdint>
#include "iomemorymapped.h"

class IO_Registers : public IOMemoryMapped {
    uint8_t joy_state[2];
    uint8_t joy_shift[2];
    bool strobe;
public:
    /*
     *  NES Controller Button Mapping (JOY1/JOY2)
     *
     *  +-----+-----+-----+--------+-------+-----+------+-------+-------+
     *  | Bit |  7  |  6  |   5    |   4   |  3  |  2   |   1   |   0   |
     *  +-----+-----+-----+--------+-------+-----+------+-------+-------+
     *  | Btn |Right|Left | Down   |  Up   |Start|Select|   B   |   A   |
     *  +-----+-----+-----+--------+-------+-----+------+-------+-------+
     */
    enum buttons {
        BUTTON_A      = (1U << 0), // Bit 0
        BUTTON_B      = (1U << 1), // Bit 1
        BUTTON_SELECT = (1U << 2), // Bit 2
        BUTTON_START  = (1U << 3), // Bit 3
        BUTTON_UP     = (1U << 4), // Bit 4
        BUTTON_DOWN   = (1U << 5), // Bit 5
        BUTTON_LEFT   = (1U << 6), // Bit 6
        BUTTON_RIGHT  = (1U << 7)  // Bit 7
    };

    explicit IO_Registers();
    virtual ~IO_Registers();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
    void set_button(uint8_t joy, buttons button);
    void clear_button(uint8_t joy, buttons button);
    void clear_buttons();
};

#endif
