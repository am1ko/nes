#ifndef MOCKMEMORY_H
#define MOCKMEMORY_H

#include "gmock/gmock.h"
#include "imemory.h"

class MockMemory: public IMemory
{
public:
    MOCK_METHOD1(read, uint8_t(uint16_t addr));
};

#endif
