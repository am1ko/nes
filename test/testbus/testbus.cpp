#include "testbus.h"
#include "bus.h"
#include "memorymap.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
BusTest::BusTest() : bus(mock_ram, mock_rom, mock_ppu, mock_apu) {
}

// ---------------------------------------------------------------------------------------------- //
BusTest::~BusTest() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(BusTest, ReadRAMStart) {
    uint16_t const addr = MemoryMap::RAM_START;
    uint8_t const val = 0xABU;
    EXPECT_CALL(mock_ram, read(addr)).WillOnce(Return(val));

    uint8_t const ret = bus.read(addr);

    EXPECT_EQ(ret, val);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BusTest, ReadRAMEnd) {
    uint16_t const addr = MemoryMap::RAM_END;
    uint8_t const val = 0xBBU;
    EXPECT_CALL(mock_ram, read(addr)).WillOnce(Return(val));

    uint8_t const ret = bus.read(addr);

    EXPECT_EQ(ret, val);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BusTest, ReadPPU_RegsStart) {
    uint16_t const addr = MemoryMap::PPU_START;
    uint8_t const val = 0x11U;
    EXPECT_CALL(mock_ppu, read(addr)).WillOnce(Return(val));

    uint8_t const ret = bus.read(addr);

    EXPECT_EQ(ret, val);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BusTest, ReadPPU_RegsEnd) {
    uint16_t const addr = 0x2007U;
    uint8_t const val = 0x22U;
    EXPECT_CALL(mock_ppu, read(addr)).WillOnce(Return(val));

    uint8_t const ret = bus.read(addr);

    EXPECT_EQ(ret, val);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BusTest, ReadROMStart) {
    uint16_t const addr = MemoryMap::ROM_START;
    uint8_t const val = 0x33U;
    EXPECT_CALL(mock_rom, read(addr)).WillOnce(Return(val));

    uint8_t const ret = bus.read(addr);

    EXPECT_EQ(ret, val);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(BusTest, ReadROMEnd) {
    uint16_t const addr = MemoryMap::ROM_END;
    uint8_t const val = 0x44U;
    EXPECT_CALL(mock_rom, read(addr)).WillOnce(Return(val));

    uint8_t const ret = bus.read(addr);

    EXPECT_EQ(ret, val);
}
