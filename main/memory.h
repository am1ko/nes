#include "imemory.h"
#include <string>
#include <fstream>

class Memory : public IMemory
{
    std::ifstream file;
public:
    explicit Memory(std::string& file);
    ~Memory();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};
