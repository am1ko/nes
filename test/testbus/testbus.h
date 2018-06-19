#include "gtest/gtest.h"
#include "mockmemory.h"
#include "bus.h"

class BusTest : public ::testing::Test {

protected:

    BusTest();
    virtual ~BusTest();

    Bus bus;
    MockMemory mock_ram;
    MockMemory mock_rom_lower;
    MockMemory mock_rom_upper;
    MockMemory mock_ppu;
    MockMemory mock_apu;
};
