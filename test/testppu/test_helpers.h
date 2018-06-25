#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#define VBLANKF               ((ppu.registers.PPUSTATUS & 0x80U) == 0x80U)

#define EXPECT_MEM_READ_8(addr, val)      EXPECT_CALL(bus, read(addr)).WillOnce(Return(val))
#define EXPECT_MEM_WRITE_8(addr, val)     EXPECT_CALL(bus, write(addr, val))
#define EXPECT_OAM_WRITE(addr, val)       EXPECT_CALL(oam, write(addr, val))
#define EXPECT_OAM_READ(addr, val)        EXPECT_CALL(oam, read(addr)).WillRepeatedly(Return(val))

#endif