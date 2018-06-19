#include "ines_parser_ifstream.h"
#include "memorymap.h"
#include <cassert>

static constexpr std::size_t INES_HEADER_SIZE = 16;
static constexpr std::size_t INES_NUM_PRG_ROM_OFFSET = 4;
static constexpr std::size_t INES_NUM_CHR_ROM_OFFSET = 5;

// ---------------------------------------------------------------------------------------------- //
INES_parser_ifstream::INES_parser_ifstream(std::string& fname)  : file(fname, std::ios::in | std::ios::binary) {
    if (file) {
        file.seekg (0, file.end);
        size_t const file_size = file.tellg();
        file.seekg (0, file.beg);
        assert(file_size > INES_HEADER_SIZE);

        char ines_header[INES_HEADER_SIZE];
        file.get(ines_header, INES_HEADER_SIZE);

        num_prg_rom_banks = (uint8_t)ines_header[INES_NUM_PRG_ROM_OFFSET];
        num_chr_rom_banks = (uint8_t)ines_header[INES_NUM_CHR_ROM_OFFSET];

        assert(file_size >= (num_prg_rom_banks*PRG_ROM_SIZE + num_chr_rom_banks*CHR_ROM_SIZE
                            + INES_HEADER_SIZE));
    }
}

// ---------------------------------------------------------------------------------------------- //
void INES_parser_ifstream::write_chr_rom(uint8_t bank, std::array<uint8_t, CHR_ROM_SIZE>& chr_rom_storage) {
    assert(bank < num_chr_rom_banks);
    assert(chr_rom_storage.size() >= CHR_ROM_SIZE);
    file.seekg(INES_HEADER_SIZE + num_prg_rom_banks*PRG_ROM_SIZE + bank*CHR_ROM_SIZE);
    file.read((char*)chr_rom_storage.data(), CHR_ROM_SIZE);
}

// ---------------------------------------------------------------------------------------------- //
void INES_parser_ifstream::write_prg_rom(uint8_t bank, std::array<uint8_t, PRG_ROM_SIZE>& prg_rom_storage) {
    assert(bank < num_prg_rom_banks);
    assert(prg_rom_storage.size() >= PRG_ROM_SIZE);
    file.seekg(INES_HEADER_SIZE + bank*PRG_ROM_SIZE);
    file.read((char*)prg_rom_storage.data(), PRG_ROM_SIZE);
}

// ---------------------------------------------------------------------------------------------- //
INES_parser_ifstream::~INES_parser_ifstream() {
    file.close();
}
