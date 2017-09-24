#include "memory.h"
// #include <iostream>

// ---------------------------------------------------------------------------------------------- //
Memory::Memory(std::string& fname) : file(fname, std::ios::in | std::ios::binary) {
    if (file) {
        // get length of file:
        file.seekg (0, file.end);
        int length = file.tellg();
        file.seekg (0, file.beg);
        // std::cout << "rom size " << std::hex << length << std::endl;
    }
}

// ---------------------------------------------------------------------------------------------- //
Memory::~Memory() {
    file.close();
}

// ---------------------------------------------------------------------------------------------- //
uint8_t Memory::read(uint16_t addr) {
    uint8_t ret;
    uint16_t const offset = 16 + addr - 0xC000U;

    file.seekg(offset);
    file.get((char&)ret);

    // std::cout << "read from " << std::hex << addr << " file offset " << offset << " return "
    //           << std::hex << static_cast<int>(ret) << std::endl;

    return ret;
}

// ---------------------------------------------------------------------------------------------- //
void Memory::write(uint16_t addr, uint8_t value) {
    // std::cout << "write " << std::hex << value << " to " << std::hex << addr << std::endl;
}