#include "testppu.h"
#include "ppu.h"
#include "test_helpers.h"
#include "cpu_interrupt.h"

using ::testing::Return;
using ::testing::Exactly;
using ::testing::_;

// ---------------------------------------------------------------------------------------------- //
PpuTest::PpuTest() : ppu() {
}

// ---------------------------------------------------------------------------------------------- //
PpuTest::~PpuTest() {};

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, ResetState) {
    ppu.reset();

    EXPECT_EQ(ppu.registers.PPUCTRL,   0x00U);
    EXPECT_EQ(ppu.registers.PPUMASK,   0x00U);
    EXPECT_EQ(ppu.registers.PPUSTATUS, 0x00U);
    EXPECT_EQ(ppu.registers.OAMADDR,   0x00U);
    EXPECT_EQ(ppu.registers.PPUSCROLL, 0x00U);
    EXPECT_EQ(ppu.registers.PPUADDR,   0x00U);
    EXPECT_EQ(ppu.registers.PPUDATA,   0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, VBlankFalseDuringVisibleFrame) {
    ppu.reset();

    for (int scan_line = 0; scan_line < 241; scan_line++) {
        for (int tick = 0; tick < 341; tick++) {
            ppu.tick();
            EXPECT_EQ(VBLANKF, false);
        }
    }

    // first tick of line 241 must still not enable VBLANK
    ppu.tick();

    EXPECT_EQ(VBLANKF, false);
    EXPECT_EQ(ppu.read(Ppu::ADDR_PPUSTATUS) & 0x80U, 0x00U);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, VBlankSetAfterPostRenderLine) {
    ppu.reset();

    for (int scan_line = 0; scan_line < 241; scan_line++) {
        for (int tick = 0; tick < 341; tick++) {
            ppu.tick();
        }
    }
    // scan line 241 tick 0
    ppu.tick();

    // scan line 241 tick 1 => VBLANK starts here
    ppu.tick();
    EXPECT_EQ(VBLANKF, true);

    // rest of scan line 241
    for (int tick = 2; tick < 341; tick++) {
        ppu.tick();
        EXPECT_EQ(VBLANKF, true);
    }
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, VBlankSetAfterPostRenderLineReadClears) {
    ppu.reset();

    for (int scan_line = 0; scan_line < 241; scan_line++) {
        for (int tick = 0; tick < 341; tick++) {
            ppu.tick();
        }
    }
    // scan line 241 tick 0
    ppu.tick();

    // scan line 241 tick 1 => VBLANK starts here
    ppu.tick();
    EXPECT_EQ(ppu.read(Ppu::ADDR_PPUSTATUS) & 0x80U, 0x80U);

    // rest of scan line 241
    for (int tick = 2; tick < 341; tick++) {
        ppu.tick();
        EXPECT_EQ(ppu.read(Ppu::ADDR_PPUSTATUS) & 0x80U, 0x00U);
    }
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, VBlankTriggersNmiInterrupt) {
    EXPECT_CALL(cpu_interrupt, set_interrupt_pending(CpuInterrupt::InterruptSource::NMI));

    ppu.reset();
    ppu.set_interrupt_handler(&cpu_interrupt);
    for (int scan_line = 0; scan_line < 241; scan_line++) {
        for (int tick = 0; tick < 341; tick++) {
            ppu.tick();
        }
    }
    // scan line 241 tick 0
    ppu.tick();
    // scan line 241 tick 1 => VBLANK starts here
    ppu.tick();
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, VBlankOn) {
    ppu.reset();

    for (int scan_line = 0; scan_line < 242; scan_line++) {
        for (int tick = 0; tick < 341; tick++) {
            ppu.tick();
        }
    }
    // scan lines 242 - 260 => VBLANK stays on
    for (int scan_line = 242; scan_line < 261; scan_line++) {
        for (int tick = 0; tick < 341; tick++) {
            ppu.tick();
            EXPECT_EQ(VBLANKF, true);
        }
    }
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, VblankEndsOnPreRenderLine) {
    ppu.reset();

    for (int scan_line = 0; scan_line < 261; scan_line++) {
        for (int tick = 0; tick < 341; tick++) {
            ppu.tick();
        }
    }

    // scan line 261 tick 0, last tick with VBLANK on
    ppu.tick();
    EXPECT_EQ(VBLANKF, true);

    // scan line 261 tick 1, VBLANK ends
    ppu.tick();
    EXPECT_EQ(VBLANKF, false);
}

// ---------------------------------------------------------------------------------------------- //
TEST_F(PpuTest, VblankOffForPreRenderLine) {
    ppu.reset();

    for (int scan_line = 0; scan_line < 261; scan_line++) {
        for (int tick = 0; tick < 341; tick++) {
            ppu.tick();
        }
    }

    // scan line 261 tick 0, last tick with VBLANK on
    ppu.tick();
    // scan line 261 tick 1, VBLANK ends
    ppu.tick();

    // rest of scan line 261
    for (int tick = 2; tick < 341; tick++) {
        ppu.tick();
        EXPECT_EQ(VBLANKF, false);
    }
}