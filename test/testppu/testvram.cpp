#include "testvram.h"
#include "ppu.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
PpuVramTest::PpuVramTest() : ppu(bus){
    ppu.reset();
}

// ---------------------------------------------------------------------------------------------- //
PpuVramTest::~PpuVramTest() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, Write2000) {
    EXPECT_MEM_WRITE_8(0x2000U, 0x01U);

    ppu.write(Ppu::ADDR_PPUADDR, 0x20U);
    ppu.write(Ppu::ADDR_PPUADDR, 0x00U);

    ppu.write(Ppu::ADDR_PPUDATA, 0x01U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, Write2108) {
    EXPECT_MEM_WRITE_8(0x2108U, 0xABU);

    ppu.write(Ppu::ADDR_PPUADDR, 0x21U);
    ppu.write(Ppu::ADDR_PPUADDR, 0x08U);

    ppu.write(Ppu::ADDR_PPUDATA, 0xABU);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, Read2001) {
    EXPECT_MEM_READ_8(0x2001U, 0x02U);

    ppu.write(Ppu::ADDR_PPUADDR, 0x20U);
    ppu.write(Ppu::ADDR_PPUADDR, 0x01U);

    uint8_t const ret = ppu.read(Ppu::ADDR_PPUDATA);

    EXPECT_EQ(ret, 0x02U);
}