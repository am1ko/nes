#include "testvram.h"
#include "ppu.h"
#include "test_helpers.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
PpuVramTest::PpuVramTest() : ppu(bus, oam, renderer) {
    ppu.reset();
}

// ---------------------------------------------------------------------------------------------- //
PpuVramTest::~PpuVramTest() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, Write) {
    EXPECT_MEM_WRITE_8(0x2000U, 0x01U);

    ppu.write(Ppu::ADDR_PPUADDR, 0x20U);
    ppu.write(Ppu::ADDR_PPUADDR, 0x00U);

    ppu.write(Ppu::ADDR_PPUDATA, 0x01U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, WriteAutoIncrementByOne) {
    EXPECT_MEM_WRITE_8(0x2108U, 0xABU);
    EXPECT_MEM_WRITE_8(0x2109U, 0xCDU);

    ppu.write(Ppu::ADDR_PPUCTRL, 0x00U);    // <-- Set to 'increment by 1' mode
    ppu.write(Ppu::ADDR_PPUADDR, 0x21U);    // <-- Set MSB of address
    ppu.write(Ppu::ADDR_PPUADDR, 0x08U);    // <-- Set LSB of address
    ppu.write(Ppu::ADDR_PPUDATA, 0xABU);    // <-- First data byte
    ppu.write(Ppu::ADDR_PPUDATA, 0xCDU);    // <-- Second data byte
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, WriteAutoIncrementByThirtyTwo) {
    EXPECT_MEM_WRITE_8(0x2108U, 0xABU);
    EXPECT_MEM_WRITE_8(0x2128U, 0xCDU);

    ppu.write(Ppu::ADDR_PPUCTRL, 0x04U);    // <-- Set to 'increment by 32' mode
    ppu.write(Ppu::ADDR_PPUADDR, 0x21U);    // <-- Set MSB of address
    ppu.write(Ppu::ADDR_PPUADDR, 0x08U);    // <-- Set LSB of address
    ppu.write(Ppu::ADDR_PPUDATA, 0xABU);    // <-- First data byte
    ppu.write(Ppu::ADDR_PPUDATA, 0xCDU);    // <-- Second data byte
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, Read) {
    EXPECT_MEM_READ_8(0x2001U, 0x02U);

    ppu.write(Ppu::ADDR_PPUADDR, 0x20U);
    ppu.write(Ppu::ADDR_PPUADDR, 0x01U);

    uint8_t const ret = ppu.read(Ppu::ADDR_PPUDATA);

    EXPECT_EQ(ret, 0x02U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, ReadAutoIncrementByOne) {
    EXPECT_MEM_READ_8(0x2001U, 0x02U);
    EXPECT_MEM_READ_8(0x2002U, 0x03U);

    ppu.write(Ppu::ADDR_PPUCTRL, 0x00U);    // <-- Set to 'increment by 1' mode
    ppu.write(Ppu::ADDR_PPUADDR, 0x20U);    // <-- Set MSB of address
    ppu.write(Ppu::ADDR_PPUADDR, 0x01U);    // <-- Set LSB of address

    uint8_t ret_1 = ppu.read(Ppu::ADDR_PPUDATA);
    uint8_t ret_2 = ppu.read(Ppu::ADDR_PPUDATA);

    EXPECT_EQ(ret_1, 0x02U);
    EXPECT_EQ(ret_2, 0x03U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, ReadAutoIncrementByThirtyTwo) {
    EXPECT_MEM_READ_8(0x2001U, 0x02U);
    EXPECT_MEM_READ_8(0x2021U, 0x03U);

    ppu.write(Ppu::ADDR_PPUCTRL, 0x04U);    // <-- Set to 'increment by 32' mode
    ppu.write(Ppu::ADDR_PPUADDR, 0x20U);    // <-- Set MSB of address
    ppu.write(Ppu::ADDR_PPUADDR, 0x01U);    // <-- Set LSB of address

    uint8_t ret_1 = ppu.read(Ppu::ADDR_PPUDATA);
    uint8_t ret_2 = ppu.read(Ppu::ADDR_PPUDATA);

    EXPECT_EQ(ret_1, 0x02U);
    EXPECT_EQ(ret_2, 0x03U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, OAMWrite) {
    EXPECT_OAM_WRITE(0x20U, 0x05U);

    ppu.write(Ppu::ADDR_OAMADDR, 0x20U);
    ppu.write(Ppu::ADDR_OAMDATA, 0x05U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, OAMWriteAutoIncrementByOne) {
    EXPECT_OAM_WRITE(0xF0U, 0xABU);
    EXPECT_OAM_WRITE(0xF1U, 0xBAU);

    ppu.write(Ppu::ADDR_OAMADDR, 0xF0U);    // <-- Set address
    ppu.write(Ppu::ADDR_OAMDATA, 0xABU);    // <-- First data byte
    ppu.write(Ppu::ADDR_OAMDATA, 0xBAU);    // <-- Second data byte
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, OAMRead) {
    EXPECT_OAM_READ(0x01U, 0x33U);

    ppu.write(Ppu::ADDR_OAMADDR, 0x01U);

    uint8_t const ret = ppu.read(Ppu::ADDR_OAMDATA);

    EXPECT_EQ(ret, 0x33U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuVramTest, OAMReadNoAutoIncrement) {
    EXPECT_OAM_READ(0x01U, 0x33U);
    EXPECT_OAM_READ(0x01U, 0x33U);

    ppu.write(Ppu::ADDR_OAMADDR, 0x01U);

    uint8_t ret = ppu.read(Ppu::ADDR_OAMDATA);
    ret = ppu.read(Ppu::ADDR_OAMDATA);

    EXPECT_EQ(ret, 0x33U);
}
