#include <array>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <boost/format.hpp>
#include "ram.h"
#include "rom.h"
#include "ines_parser_ifstream.h"
#include "io_registers.h"
#include "bus.h"
#include "cpu.h"
#include "ppu.h"
#include "bus_ppu.h"

static unsigned ppu_cycles;

// ---------------------------------------------------------------------------------------------- //
class StdOutLogger : public ICpuLogger {
public:
    void log(uint8_t const * instr, uint8_t bytes, uint16_t instr_addr, uint8_t cycles,
             struct CpuContext const * const context);
};

// ---------------------------------------------------------------------------------------------- //
void StdOutLogger::log(uint8_t const * instr, uint8_t bytes, uint16_t instr_addr, uint8_t cycles,
                       struct CpuContext const * const context) {
    std::cout << boost::format("%04X  ") % instr_addr;

    for (int i = 0; i < 3; i++) {
        if (bytes > i) {
            std::cout << boost::format("%02X ") % static_cast<int>(instr[i]);
        } else {
            std::cout << "   ";
        }
    }

    // TODO(amiko): disassembly
    std::cout << boost::format("%-20s") % "";

    std::cout << boost::format("A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%3u \n")
    % static_cast<int>(context->sregs[A]) % static_cast<int>(context->sregs[X])
    % static_cast<int>(context->sregs[Y]) % static_cast<int>(context->P)
    % static_cast<int>(context->SP) % (ppu_cycles);
}

static constexpr std::size_t CPU_RAM_SIZE = (2*1024);
static constexpr std::size_t PPU_RAM_SIZE = (2*1024);

static std::array<uint8_t, CPU_RAM_SIZE> cpu_ram_storage;
static std::array<uint8_t, PPU_RAM_SIZE> ppu_ram_storage;
static std::array<uint8_t, CHR_ROM_SIZE> chr_rom_storage;
static std::array<uint8_t, PRG_ROM_SIZE> prg_rom_storage_lower;
static std::array<uint8_t, PRG_ROM_SIZE> prg_rom_storage_upper;

// ---------------------------------------------------------------------------------------------- //
static void debug_draw(void) {
    std::cout << "-----------------------------------------------------------------------------------"
    "-----------------" << std::endl;
    for (unsigned row = 0; row < 30; row++) {
        std::cout << "[ ";
        for (unsigned col = 0; col < 32; col++) {
            // std::cout << " " <<  (int)ppu_ram[row*30 + col] << " ";
            std::cout << boost::format("%02X ") % static_cast<int>(ppu_ram_storage[row*32 + col]);
            // std::cout << boost::format("%02X ") % static_cast<int>(vram.read(row*32 + col));
        }
        std::cout << " ]" << std::endl;
    }
    std::cout << "-----------------------------------------------------------------------------------"
    "-----------------" << std::endl;
    std::system("clear");
}

// ---------------------------------------------------------------------------------------------- //
int main(int argc, char **argv)
{
    assert(argc == 2);
    std::string file = std::string(argv[1]);

    StdOutLogger logger;

    ROM <PRG_ROM_SIZE> prg_rom_lower(prg_rom_storage_lower);
    ROM <PRG_ROM_SIZE> prg_rom_upper(prg_rom_storage_upper);
    ROM <CHR_ROM_SIZE> chr_rom(chr_rom_storage);
    RAM <CPU_RAM_SIZE> cpu_ram(cpu_ram_storage);
    RAM <PPU_RAM_SIZE> ppu_ram(ppu_ram_storage);

    {
        INES_parser_ifstream ines_parser(file);

        assert(ines_parser.num_prg_rom_banks < 3);
        assert(ines_parser.num_chr_rom_banks == 1);

        ines_parser.write_chr_rom(0U, chr_rom_storage);
        ines_parser.write_prg_rom(0U, prg_rom_storage_lower);

        if (ines_parser.num_prg_rom_banks == 2) {
            ines_parser.write_prg_rom(1U, prg_rom_storage_upper);
        }
        else {
            ines_parser.write_prg_rom(0U, prg_rom_storage_upper);
        }
    }

    IO_Registers io_registers;
    BusPpu ppu_bus(ppu_ram, chr_rom);
    Ppu ppu(ppu_bus);
    Bus bus(cpu_ram, prg_rom_lower, prg_rom_upper, ppu, io_registers);
    Cpu cpu(bus);
    // cpu.set_logger(&logger);

    cpu.reset();
    ppu.reset();

    cpu.context.PC = 0xC000U;

    unsigned ret = 0U;
    unsigned instructions = 0U;
    do {
        ret = cpu.tick();
        ppu_cycles = (ppu_cycles + ret*3U) % 341U;

        for (unsigned i = 0U; i < ret*3U; i++) {
            bool const irq = ppu.tick();
            if (irq) {
                cpu.set_interrupt_pending(CpuInterrupt::InterruptSource::NMI);
                debug_draw();
            }
        }

        instructions++;
    } while(ret != 0U);

    std::cout << "Unknown instruction" << std::endl;
    std::cout << std::dec << instructions - 1 <<  " instructions executed" << std::endl;

    return 0;
}
