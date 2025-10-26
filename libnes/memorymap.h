#ifndef MEMORYMAP_H
#define MEMORYMAP_H

#include <cstdint>

namespace MemoryMap{
    constexpr uint16_t RAM_START            = 0x0000U;
    constexpr uint16_t RAM_MIRROR_START     = 0x0800U;
    constexpr uint16_t RAM_END              = 0x1FFFU;
    constexpr uint16_t IO_REGISTERS_START   = 0x2000U;
    constexpr uint16_t PPU_START            = 0x2000U;
    constexpr uint16_t PPU_END              = 0x3FFFU;
    constexpr uint16_t OAM_DMA              = 0x4014U;
    constexpr uint16_t IO_JOY1              = 0x4016U;
    constexpr uint16_t IO_JOY2              = 0x4017U;
    constexpr uint16_t IO_REGISTERS_END     = 0x401FU;
    constexpr uint16_t EXPANSION_ROM_START  = 0x4020U;
    constexpr uint16_t EXPANSION_ROM_END    = 0x5FFFU;
    constexpr uint16_t SRAM_START           = 0x6000U;
    constexpr uint16_t SRAM_END             = 0x7FFFU;
    constexpr uint16_t ROM_START            = 0x8000U;
    constexpr uint16_t ROM_LOWER_BANK_START = 0x8000U;
    constexpr uint16_t ROM_LOWER_BANK_END   = 0xBFFFU;
    constexpr uint16_t ROM_UPPER_BANK_START = 0xC000U;
    constexpr uint16_t ROM_UPPER_BANK_END   = 0xFFFFU;
    constexpr uint16_t ROM_END              = 0xFFFFU;
}

#endif