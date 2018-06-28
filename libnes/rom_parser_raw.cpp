#include "rom_parser_raw.h"
#include "memorymap.h"
#include <cassert>
#include <cstring>

static constexpr std::size_t INES_HEADER_SIZE = 16;
static constexpr std::size_t INES_NUM_PRG_ROM_OFFSET = 4;
static constexpr std::size_t INES_NUM_CHR_ROM_OFFSET = 5;

// ---------------------------------------------------------------------------------------------- //
ROM_parser_raw::ROM_parser_raw(uint8_t const * rom_contents, size_t size) : rom_contents(rom_contents) {
    if (rom_contents) {
        assert(size > INES_HEADER_SIZE);

        num_prg_rom_banks = (uint8_t)rom_contents[INES_NUM_PRG_ROM_OFFSET];
        num_chr_rom_banks = (uint8_t)rom_contents[INES_NUM_CHR_ROM_OFFSET];

        assert(size >= (num_prg_rom_banks*PRG_ROM_SIZE + num_chr_rom_banks*CHR_ROM_SIZE
                            + INES_HEADER_SIZE));
    }
}

// ---------------------------------------------------------------------------------------------- //
void ROM_parser_raw::write_chr_rom(uint8_t bank, std::array<uint8_t, CHR_ROM_SIZE>& chr_rom_storage) {
    assert(bank < num_chr_rom_banks);
    assert(chr_rom_storage.size() >= CHR_ROM_SIZE);

    memcpy((char*)chr_rom_storage.data(),
           &rom_contents[INES_HEADER_SIZE + num_prg_rom_banks*PRG_ROM_SIZE + bank*CHR_ROM_SIZE],
           CHR_ROM_SIZE);
}

// ---------------------------------------------------------------------------------------------- //
void ROM_parser_raw::write_prg_rom(uint8_t bank, std::array<uint8_t, PRG_ROM_SIZE>& prg_rom_storage) {
    assert(bank < num_prg_rom_banks);
    assert(prg_rom_storage.size() >= PRG_ROM_SIZE);

    memcpy((char*)prg_rom_storage.data(),
           &rom_contents[INES_HEADER_SIZE + bank*PRG_ROM_SIZE],
           PRG_ROM_SIZE);

}

// ---------------------------------------------------------------------------------------------- //
ROM_parser_raw::~ROM_parser_raw() {
}
