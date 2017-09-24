#include <cassert>
#include <iostream>
#include <iomanip>
#include <boost/format.hpp>
#include "memory.h"
#include "cpu.h"

// ---------------------------------------------------------------------------------------------- //
class StdOutLogger : public ICpuLogger {
public:
    void log(uint8_t instr, uint16_t instr_addr, uint16_t param_addr,
             struct CpuContext const * const context);
};

// ---------------------------------------------------------------------------------------------- //
void StdOutLogger::log(uint8_t instr, uint16_t instr_addr, uint16_t param_addr,
             struct CpuContext const * const context) {
    std::cout << boost::format("%-06X%-03X%-03X%-03X")
    % instr_addr % static_cast<int>(instr) % (param_addr & 0xFFU) % ((param_addr & 0xFF00) >> 8) ;

    // TODO(amiko): disassembly
    std::cout << boost::format("%-20s") % "";

    std::cout << boost::format("A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%d \n")
    % static_cast<int>(context->sregs[A]) % static_cast<int>(context->sregs[X])
    % static_cast<int>(context->sregs[Y]) % static_cast<int>(context->P)
    % static_cast<int>(context->SP) % 0;
}

// ---------------------------------------------------------------------------------------------- //
int main(int argc, char **argv)
{
    assert(argc == 2);
    std::string file = std::string(argv[1]);

    StdOutLogger logger;
    Memory mem(file);
    Cpu cpu(mem);
    cpu.set_logger(&logger);

    cpu.reset();

    cpu.context.PC = 0xC000U;

    cpu.tick();
    cpu.tick();
    cpu.tick();
    cpu.tick();
    cpu.tick();

    return 0;
}
