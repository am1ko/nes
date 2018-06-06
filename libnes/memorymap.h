#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <cstdint>

namespace MemoryMap{
    const uint16_t RAM_START            = 0x0000U;
    const uint16_t RAM_MIRROR_START     = 0x0800U;
    const uint16_t RAM_END              = 0x1FFFU;
    const uint16_t IO_REGISTERS_START   = 0x2000U;
    const uint16_t PPU_START            = 0x2000U;
    const uint16_t PPU_END              = 0x3FFFU;
    const uint16_t IO_REGISTERS_END     = 0x401FU;
    const uint16_t EXPANSION_ROM_START  = 0x4020U;
    const uint16_t EXPANSION_ROM_END    = 0x5FFFU;
    const uint16_t SRAM_START           = 0x6000U;
    const uint16_t SRAM_END             = 0x7FFFU;
    const uint16_t ROM_START            = 0x8000U;
    const uint16_t ROM_LOWER_BANK_START = 0x8000U;
    const uint16_t ROM_LOWER_BANK_END   = 0xBFFFU;
    const uint16_t ROM_UPPER_BANK_START = 0xC000U;
    const uint16_t ROM_UPPER_BANK_END   = 0xFFFFU;
    const uint16_t ROM_END              = 0xFFFFU;
}

#endif