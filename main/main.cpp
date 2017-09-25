#include <cassert>
#include <iostream>
#include <iomanip>
#include <boost/format.hpp>
#include "memory.h"
#include "cpu.h"

// ---------------------------------------------------------------------------------------------- //
class StdOutLogger : public ICpuLogger {
public:
    void log(uint8_t const * instr, uint8_t bytes, uint16_t instr_addr, uint8_t cycles,
             struct CpuContext const * const context);
};

// ---------------------------------------------------------------------------------------------- //
void StdOutLogger::log(uint8_t const * instr, uint8_t bytes, uint16_t instr_addr, uint8_t cycles,
                       struct CpuContext const * const context) {
    std::cout << boost::format("%-06X") % instr_addr;

    for (int i = 0; i < 3; i++) {
        if (bytes > i) {
            std::cout << boost::format("%02X ") % static_cast<int>(instr[i]);
        } else {
            std::cout << "   ";
        }
    }

    // TODO(amiko): disassembly
    std::cout << boost::format("%-20s") % "";

    std::cout << boost::format("A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%d \n")
    % static_cast<int>(context->sregs[A]) % static_cast<int>(context->sregs[X])
    % static_cast<int>(context->sregs[Y]) % static_cast<int>(context->P)
    % static_cast<int>(context->SP) % static_cast<int>(cycles);
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

    unsigned ret;
    do {
        ret = cpu.tick();
    } while(ret != 0U);

    return 0;
}
