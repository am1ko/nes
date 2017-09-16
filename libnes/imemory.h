#include <cstdint>

class IMemory
{
public:
    virtual uint8_t read(uint16_t addr) = 0;
};
