#include <cassert>
#include <iostream>
#include <iomanip>
#include <boost/format.hpp>
#include "ram.h"
#include "rom_ifstream.h"
#include "io_registers.h"
#include "bus.h"
#include "cpu.h"

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

// ---------------------------------------------------------------------------------------------- //
int main(int argc, char **argv)
{
    assert(argc == 2);
    std::string file = std::string(argv[1]);

    StdOutLogger logger;

    RAM ram;
    ROM_ifstream rom(file);
    IO_Registers io_registers;

    Bus bus(ram, rom, io_registers);
    Cpu cpu(bus);
    cpu.set_logger(&logger);

    cpu.reset();

    cpu.context.PC = 0xC000U;

    unsigned ret = 0U;
    unsigned instructions = 0U;
    do {
        ret = cpu.tick();
        ppu_cycles = (ppu_cycles + ret*3U) % 341U;
        instructions++;
    } while(ret != 0U);

    std::cout << "Unknown instruction" << std::endl;
    std::cout << std::dec << instructions - 1 <<  " instructions executed" << std::endl;

    return 0;
}
