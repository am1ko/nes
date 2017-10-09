#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#define NO_FLAGS    (0U)
#define RESULT_NONE   (&Cpu::resultmode_none)
#define RESULT_MEM    (&Cpu::resultmode_mem)
#define RESULT_A      (&Cpu::resultmode_reg_a)

// ---------------------------------------------------------------------------------------------- //
const struct CpuInstruction Cpu::instruction_set[256] = {
// INSTR ---- OPCODE --------- ADDR MODE ------ CYCLES - BYTES ------- FLAGS ---------  RESULT -- //
/* $00 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $01 */   {&Cpu::ORA,     &Cpu::addrmode_inx,   6U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $02 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $03 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $04 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $05 */   {&Cpu::ORA,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $06 */   {&Cpu::ASL,     &Cpu::addrmode_zpg,   2U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM },
/* $07 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $08 */   {&Cpu::PHP,     &Cpu::addrmode_imp,   3U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $09 */   {&Cpu::ORA,     &Cpu::addrmode_imm,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $0A */   {&Cpu::ASL_ACC, &Cpu::addrmode_imp,   2U,     1U,    (  F_C|F_Z|F_N  ),   RESULT_A   },
/* $0B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $0C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $0D */   {&Cpu::ORA,     &Cpu::addrmode_abs,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $0E */   {&Cpu::ASL,     &Cpu::addrmode_abs,   2U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM },
/* $0F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $10 */   {&Cpu::BPL,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $11 */   {&Cpu::ORA,     &Cpu::addrmode_iny,   5U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $12 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $13 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $14 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $15 */   {&Cpu::ORA,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $16 */   {&Cpu::ASL,     &Cpu::addrmode_zpx,   2U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM },
/* $17 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $18 */   {&Cpu::CLC,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $19 */   {&Cpu::ORA,     &Cpu::addrmode_aby,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $1A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $1B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $1C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $1D */   {&Cpu::ORA,     &Cpu::addrmode_abx,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $1E */   {&Cpu::ASL,     &Cpu::addrmode_abx,   2U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM },
/* $1F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $20 */   {&Cpu::JSR,     &Cpu::addrmode_abs,   6U,     3U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $21 */   {&Cpu::AND,     &Cpu::addrmode_inx,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $22 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $23 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $24 */   {&Cpu::BIT,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_Z        ),   RESULT_NONE},
/* $25 */   {&Cpu::AND,     &Cpu::addrmode_zpg,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $26 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $27 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $28 */   {&Cpu::PLP,     &Cpu::addrmode_imp,   4U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $29 */   {&Cpu::AND,     &Cpu::addrmode_imm,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $2A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $2B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $2C */   {&Cpu::BIT,     &Cpu::addrmode_abs,   4U,     3U,    (    F_Z        ),   RESULT_NONE},
/* $2D */   {&Cpu::AND,     &Cpu::addrmode_abs,   2U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $2E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $2F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $30 */   {&Cpu::BMI,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $31 */   {&Cpu::AND,     &Cpu::addrmode_iny,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $32 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $33 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $34 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $35 */   {&Cpu::AND,     &Cpu::addrmode_zpx,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $36 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $37 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $38 */   {&Cpu::SEC,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $39 */   {&Cpu::AND,     &Cpu::addrmode_aby,   2U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $3A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $3B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $3C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $3D */   {&Cpu::AND,     &Cpu::addrmode_abx,   2U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $3E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $3F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $40 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $41 */   {&Cpu::EOR,     &Cpu::addrmode_inx,   6U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $42 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $43 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $44 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $45 */   {&Cpu::EOR,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $46 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $47 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $48 */   {&Cpu::PHA,     &Cpu::addrmode_imp,   3U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $49 */   {&Cpu::EOR,     &Cpu::addrmode_imm,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $4A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $4B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $4C */   {&Cpu::JMP,     &Cpu::addrmode_abs,   3U,     3U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $4D */   {&Cpu::EOR,     &Cpu::addrmode_abs,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $4E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $4F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $50 */   {&Cpu::BVC,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $51 */   {&Cpu::EOR,     &Cpu::addrmode_iny,   5U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $52 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $53 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $54 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $55 */   {&Cpu::EOR,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_Z|F_N    ),   RESULT_A   },
/* $56 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $57 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $58 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $59 */   {&Cpu::EOR,     &Cpu::addrmode_aby,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $5A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $5B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $5C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $5D */   {&Cpu::EOR,     &Cpu::addrmode_abx,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   },
/* $5E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $5F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $60 */   {&Cpu::RTS,     &Cpu::addrmode_imm,   6U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $61 */   {&Cpu::ADC,     &Cpu::addrmode_inx,   2U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   },
/* $62 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $63 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $64 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $65 */   {&Cpu::ADC,     &Cpu::addrmode_zpg,   2U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   },
/* $66 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $67 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $68 */   {&Cpu::PLA,     &Cpu::addrmode_imp,   4U,     1U,    (    F_N|F_Z    ),   RESULT_A   },
/* $69 */   {&Cpu::ADC,     &Cpu::addrmode_imm,   2U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   },
/* $6A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $6B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $6C */   {&Cpu::JMP,     &Cpu::addrmode_ind,   5U,     3U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $6D */   {&Cpu::ADC,     &Cpu::addrmode_abs,   2U,     3U,    (F_N|F_V|F_Z|F_C),   RESULT_A   },
/* $6E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $6F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $70 */   {&Cpu::BVS,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $71 */   {&Cpu::ADC,     &Cpu::addrmode_iny,   2U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   },
/* $72 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $73 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $74 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $75 */   {&Cpu::ADC,     &Cpu::addrmode_zpx,   2U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   },
/* $76 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $77 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $78 */   {&Cpu::SEI,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $79 */   {&Cpu::ADC,     &Cpu::addrmode_aby,   2U,     3U,    (    NO_FLAGS   ),   RESULT_A   },
/* $7A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $7B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $7C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $7D */   {&Cpu::ADC,     &Cpu::addrmode_abx,   2U,     3U,    (    NO_FLAGS   ),   RESULT_A   },
/* $7E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $7F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $80 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $81 */   {&Cpu::STA,     &Cpu::addrmode_inx,   6U,     2U,    (    NO_FLAGS   ),   RESULT_MEM },
/* $82 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $83 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $84 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $85 */   {&Cpu::STA,     &Cpu::addrmode_zpg,   3U,     2U,    (    NO_FLAGS   ),   RESULT_MEM },
/* $86 */   {&Cpu::STX,     &Cpu::addrmode_zpg,   3U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $87 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $88 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $89 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $8A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $8B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $8C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $8D */   {&Cpu::STA,     &Cpu::addrmode_abs,   4U,     3U,    (    NO_FLAGS   ),   RESULT_MEM },
/* $8E */   {&Cpu::STX,     &Cpu::addrmode_abs,   4U,     3U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $8F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $90 */   {&Cpu::BCC,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $91 */   {&Cpu::STA,     &Cpu::addrmode_iny,   6U,     2U,    (    NO_FLAGS   ),   RESULT_MEM },
/* $92 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $93 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $94 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $95 */   {&Cpu::STA,     &Cpu::addrmode_zpx,   4U,     2U,    (    NO_FLAGS   ),   RESULT_MEM },
/* $96 */   {&Cpu::STX,     &Cpu::addrmode_zpy,   4U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $97 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $98 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $99 */   {&Cpu::STA,     &Cpu::addrmode_aby,   5U,     3U,    (    NO_FLAGS   ),   RESULT_MEM },
/* $9A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $9B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $9C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $9D */   {&Cpu::STA,     &Cpu::addrmode_abx,   5U,     3U,    (    NO_FLAGS   ),   RESULT_MEM },
/* $9E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $9F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $A0 */   {&Cpu::LDY,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $A1 */   {&Cpu::LDA,     &Cpu::addrmode_inx,   6U,     2U,    (    F_N|F_Z    ),   RESULT_A   },
/* $A2 */   {&Cpu::LDX,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $A3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $A4 */   {&Cpu::LDY,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $A5 */   {&Cpu::LDA,     &Cpu::addrmode_zpg,   2U,     2U,    (    F_N|F_Z    ),   RESULT_A   },
/* $A6 */   {&Cpu::LDX,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $A7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $A8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $A9 */   {&Cpu::LDA,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_A   },
/* $AA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $AB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $AC */   {&Cpu::LDY,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $AD */   {&Cpu::LDA,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_A   },
/* $AE */   {&Cpu::LDX,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $AF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $B0 */   {&Cpu::BCS,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $B1 */   {&Cpu::LDA,     &Cpu::addrmode_iny,   5U,     2U,    (    F_N|F_Z    ),   RESULT_A   },
/* $B2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $B3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $B4 */   {&Cpu::LDY,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $B5 */   {&Cpu::LDA,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_N|F_Z    ),   RESULT_A   },
/* $B6 */   {&Cpu::LDX,     &Cpu::addrmode_zpy,   4U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $B7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $B8 */   {&Cpu::CLV,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $B9 */   {&Cpu::LDA,     &Cpu::addrmode_aby,   4U,     3U,    (    F_N|F_Z    ),   RESULT_A   },
/* $BA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $BB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $BC */   {&Cpu::LDY,     &Cpu::addrmode_abx,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $BD */   {&Cpu::LDA,     &Cpu::addrmode_abx,   4U,     3U,    (    F_N|F_Z    ),   RESULT_A   },
/* $BE */   {&Cpu::LDX,     &Cpu::addrmode_aby,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $BF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $C0 */   {&Cpu::CPY,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $C1 */   {&Cpu::CMP,     &Cpu::addrmode_inx,   6U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $C2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $C3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $C4 */   {&Cpu::CPY,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $C5 */   {&Cpu::CMP,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $C6 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $C7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $C8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $C9 */   {&Cpu::CMP,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $CA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $CB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $CC */   {&Cpu::CPY,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $CD */   {&Cpu::CMP,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $CE */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $CF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $D0 */   {&Cpu::BNE,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $D1 */   {&Cpu::CMP,     &Cpu::addrmode_iny,   5U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $D2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $D3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $D4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $D5 */   {&Cpu::CMP,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $D6 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $D7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $D8 */   {&Cpu::CLD,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $D9 */   {&Cpu::CMP,     &Cpu::addrmode_aby,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $DA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $DB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $DC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $DD */   {&Cpu::CMP,     &Cpu::addrmode_abx,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE},
/* $DE */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $DF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E0 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E1 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E5 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E6 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $E9 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $EA */   {&Cpu::NOP,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $EB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $EC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $ED */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $EE */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $EF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F0 */   {&Cpu::BEQ,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F1 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F5 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F6 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F8 */   {&Cpu::SED,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $F9 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $FA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $FB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $FC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $FD */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $FE */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE},
/* $FF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE}
};

#endif
