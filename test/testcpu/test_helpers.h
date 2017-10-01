#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#define EXPECT_MEM_READ_8(addr, val)      EXPECT_CALL(memory, read(addr)).WillOnce(Return(val))
#define EXPECT_MEM_READ_16(addr, val)     EXPECT_CALL(memory, read(addr)).WillOnce(Return(val & 0xFFU)); \
                                          EXPECT_CALL(memory, read(addr+1)).WillOnce(Return((val >> 8) & 0xFFU))
#define EXPECT_MEM_WRITE_8(addr, val)     EXPECT_CALL(memory, write(addr, val))

#define REG_PC                            cpu.context.PC
#define REG_SP                            cpu.context.SP
#define REG_A                             cpu.context.sregs[A]
#define REG_X                             cpu.context.sregs[X]
#define REG_Y                             cpu.context.sregs[Y]
#define REG_P                             cpu.context.P
#define SET_REG_A(val)                    cpu.context.sregs[A] = val
#define SET_REG_X(val)                    cpu.context.sregs[X] = val
#define SET_REG_Y(val)                    cpu.context.sregs[Y] = val
#define SET_REG_PC(val)                   cpu.context.PC = val
#define SET_REG_P(val)                    cpu.context.P = val
#define SET_REG_SP(val)                   cpu.context.SP = val
#define SET_CARRYF(val)                   cpu.context.P |= ((uint8_t)val) << 0;
#define SET_ZEROF(val)                    cpu.context.P |= ((uint8_t)val) << 1;
#define SET_OVERFLOWF(val)                cpu.context.P |= ((uint8_t)val) << 6;
#define SET_NEGF(val)                     cpu.context.P |= ((uint8_t)val) << 7;

#define CARRYF                            ((cpu.context.P & 0x01U) != 0U)
#define ZEROF                             ((cpu.context.P & 0x02U) != 0U)
#define INTERRUPTF                        ((cpu.context.P & 0x04U) != 0U)
#define DECIMALF                          ((cpu.context.P & 0x08U) != 0U)
#define OVERFLOWF                         ((cpu.context.P & 0x40U) != 0U)
#define NEGF                              ((cpu.context.P & 0x80U) != 0U)

#endif