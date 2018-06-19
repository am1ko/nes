#ifndef INES_PARSER_IFSTREAM_H
#define INES_PARSER_IFSTREAM_H

#include <array>
#include <string>
#include <fstream>

constexpr std::size_t CHR_ROM_SIZE = (8*1024);
constexpr std::size_t PRG_ROM_SIZE = (16*1024);

struct INES_parser_ifstream {
    std::ifstream file;
    uint8_t num_prg_rom_banks = 0U;
    uint8_t num_chr_rom_banks = 0U;

    INES_parser_ifstream(std::string& file);
    ~INES_parser_ifstream();

    void write_chr_rom(uint8_t bank, std::array<uint8_t, CHR_ROM_SIZE>& chr_rom_storage);
    void write_prg_rom(uint8_t bank, std::array<uint8_t, PRG_ROM_SIZE>& prg_rom_storage);
};

#endif