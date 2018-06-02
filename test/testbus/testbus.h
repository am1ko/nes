#include "gtest/gtest.h"
#include "mockmemory.h"
#include "bus.h"

class BusTest : public ::testing::Test {

protected:

    BusTest();
    virtual ~BusTest();

    Bus bus;
    MockMemory mock_ram;
    MockMemory mock_rom;
    MockMemory mock_io_registers;
};