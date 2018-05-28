#ifndef MOCKMEMORY_H
#define MOCKMEMORY_H

#include "gmock/gmock.h"
#include "iomemorymapped.h"

class MockMemory: public IOMemoryMapped
{
public:
    MOCK_METHOD1(read, uint8_t(uint16_t addr));
    MOCK_METHOD2(write, void(uint16_t addr, uint8_t value));
};

#endif
