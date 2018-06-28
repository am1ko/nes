#ifndef ROM_PARSER_RAW_H
#define ROM_PARSER_RAW_H

#include <array>
#include <string>
#include <fstream>
#include <cstdint>

constexpr std::size_t CHR_ROM_SIZE = (8*1024);
constexpr std::size_t PRG_ROM_SIZE = (16*1024);

struct ROM_parser_raw{
    uint8_t num_prg_rom_banks = 0U;
    uint8_t num_chr_rom_banks = 0U;
    uint8_t const * rom_contents;

    ROM_parser_raw(uint8_t const * rom_contents, size_t size);
    ~ROM_parser_raw();

    void write_chr_rom(uint8_t bank, std::array<uint8_t, CHR_ROM_SIZE>& chr_rom_storage);
    void write_prg_rom(uint8_t bank, std::array<uint8_t, PRG_ROM_SIZE>& prg_rom_storage);
};

#endif