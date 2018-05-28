#include "iomemorymapped.h"
#include <string>
#include <fstream>

class Memory : public IOMemoryMapped
{
    std::ifstream file;
public:
    explicit Memory(std::string& file);
    ~Memory();
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
private:
    uint8_t ram[0x800U];    // 2 kB internal RAM
};
