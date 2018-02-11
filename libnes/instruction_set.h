#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#include <cstdbool>

#define NO_FLAGS    (0U)
#define RESULT_NONE   (&Cpu::resultmode_none)
#define RESULT_MEM    (&Cpu::resultmode_mem)
#define RESULT_A      (&Cpu::resultmode_reg_a)

// ---------------------------------------------------------------------------------------------- //
const struct CpuInstruction Cpu::instruction_set[256] = {
// INSTR ---- OPCODE --------- ADDR MODE ------ CYCLES - BYTES ------- FLAGS ---------  RESULT -- //
/* $00 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $01 */   {&Cpu::ORA,     &Cpu::addrmode_inx,   6U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $02 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $03 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $04 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $05 */   {&Cpu::ORA,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $06 */   {&Cpu::ASL,     &Cpu::addrmode_zpg,   5U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $07 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $08 */   {&Cpu::PHP,     &Cpu::addrmode_imp,   3U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $09 */   {&Cpu::ORA,     &Cpu::addrmode_imm,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $0A */   {&Cpu::ASL,     &Cpu::addrmode_imp,   2U,     1U,    (  F_C|F_Z|F_N  ),   RESULT_A   , true },
/* $0B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $0C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $0D */   {&Cpu::ORA,     &Cpu::addrmode_abs,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $0E */   {&Cpu::ASL,     &Cpu::addrmode_abs,   6U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $0F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $10 */   {&Cpu::BPL,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $11 */   {&Cpu::ORA,     &Cpu::addrmode_iny,   5U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $12 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $13 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $14 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $15 */   {&Cpu::ORA,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $16 */   {&Cpu::ASL,     &Cpu::addrmode_zpx,   6U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $17 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $18 */   {&Cpu::CLC,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $19 */   {&Cpu::ORA,     &Cpu::addrmode_aby,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $1A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $1B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $1C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $1D */   {&Cpu::ORA,     &Cpu::addrmode_abx,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $1E */   {&Cpu::ASL,     &Cpu::addrmode_abx,   7U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $1F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $20 */   {&Cpu::JSR,     &Cpu::addrmode_abs,   6U,     3U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $21 */   {&Cpu::AND,     &Cpu::addrmode_inx,   6U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $22 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $23 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $24 */   {&Cpu::BIT,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_Z        ),   RESULT_NONE, false},
/* $25 */   {&Cpu::AND,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $26 */   {&Cpu::ROL,     &Cpu::addrmode_zpg,   5U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $27 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $28 */   {&Cpu::PLP,     &Cpu::addrmode_imp,   4U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $29 */   {&Cpu::AND,     &Cpu::addrmode_imm,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $2A */   {&Cpu::ROL,     &Cpu::addrmode_imp,   2U,     1U,    (  F_C|F_Z|F_N  ),   RESULT_A   , true },
/* $2B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $2C */   {&Cpu::BIT,     &Cpu::addrmode_abs,   4U,     3U,    (    F_Z        ),   RESULT_NONE, false},
/* $2D */   {&Cpu::AND,     &Cpu::addrmode_abs,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $2E */   {&Cpu::ROL,     &Cpu::addrmode_abs,   6U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $2F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $30 */   {&Cpu::BMI,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $31 */   {&Cpu::AND,     &Cpu::addrmode_iny,   5U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $32 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $33 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $34 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $35 */   {&Cpu::AND,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $36 */   {&Cpu::ROL,     &Cpu::addrmode_zpx,   6U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $37 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $38 */   {&Cpu::SEC,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $39 */   {&Cpu::AND,     &Cpu::addrmode_aby,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $3A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $3B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $3C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $3D */   {&Cpu::AND,     &Cpu::addrmode_abx,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $3E */   {&Cpu::ROL,     &Cpu::addrmode_abx,   7U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $3F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $40 */   {&Cpu::RTI,     &Cpu::addrmode_imp,   6U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $41 */   {&Cpu::EOR,     &Cpu::addrmode_inx,   6U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $42 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $43 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $44 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $45 */   {&Cpu::EOR,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $46 */   {&Cpu::LSR,     &Cpu::addrmode_zpg,   5U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $47 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $48 */   {&Cpu::PHA,     &Cpu::addrmode_imp,   3U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $49 */   {&Cpu::EOR,     &Cpu::addrmode_imm,   2U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $4A */   {&Cpu::LSR,     &Cpu::addrmode_imp,   2U,     1U,    (  F_C|F_Z|F_N  ),   RESULT_A   , true },
/* $4B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $4C */   {&Cpu::JMP,     &Cpu::addrmode_abs,   3U,     3U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $4D */   {&Cpu::EOR,     &Cpu::addrmode_abs,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $4E */   {&Cpu::LSR,     &Cpu::addrmode_abs,   6U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $4F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $50 */   {&Cpu::BVC,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $51 */   {&Cpu::EOR,     &Cpu::addrmode_iny,   5U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $52 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $53 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $54 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $55 */   {&Cpu::EOR,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $56 */   {&Cpu::LSR,     &Cpu::addrmode_zpx,   6U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $57 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $58 */   {&Cpu::CLI,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $59 */   {&Cpu::EOR,     &Cpu::addrmode_aby,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $5A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $5B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $5C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $5D */   {&Cpu::EOR,     &Cpu::addrmode_abx,   4U,     3U,    (    F_Z|F_N    ),   RESULT_A   , false},
/* $5E */   {&Cpu::LSR,     &Cpu::addrmode_abx,   7U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $5F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $60 */   {&Cpu::RTS,     &Cpu::addrmode_imm,   6U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $61 */   {&Cpu::ADC,     &Cpu::addrmode_inx,   6U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $62 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $63 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $64 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $65 */   {&Cpu::ADC,     &Cpu::addrmode_zpg,   3U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $66 */   {&Cpu::ROR,     &Cpu::addrmode_zpg,   5U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $67 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $68 */   {&Cpu::PLA,     &Cpu::addrmode_imp,   4U,     1U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $69 */   {&Cpu::ADC,     &Cpu::addrmode_imm,   2U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $6A */   {&Cpu::ROR,     &Cpu::addrmode_imp,   2U,     1U,    (  F_C|F_Z|F_N  ),   RESULT_A   , true },
/* $6B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $6C */   {&Cpu::JMP,     &Cpu::addrmode_ind,   5U,     3U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $6D */   {&Cpu::ADC,     &Cpu::addrmode_abs,   4U,     3U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $6E */   {&Cpu::ROR,     &Cpu::addrmode_abs,   6U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $6F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $70 */   {&Cpu::BVS,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $71 */   {&Cpu::ADC,     &Cpu::addrmode_iny,   5U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $72 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $73 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $74 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $75 */   {&Cpu::ADC,     &Cpu::addrmode_zpx,   4U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $76 */   {&Cpu::ROR,     &Cpu::addrmode_zpx,   6U,     2U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $77 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $78 */   {&Cpu::SEI,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $79 */   {&Cpu::ADC,     &Cpu::addrmode_aby,   4U,     3U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $7A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $7B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $7C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $7D */   {&Cpu::ADC,     &Cpu::addrmode_abx,   4U,     3U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $7E */   {&Cpu::ROR,     &Cpu::addrmode_abx,   7U,     3U,    (  F_C|F_Z|F_N  ),   RESULT_MEM , false},
/* $7F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $80 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $81 */   {&Cpu::STA,     &Cpu::addrmode_inx,   6U,     2U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $82 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $83 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $84 */   {&Cpu::STY,     &Cpu::addrmode_zpg,   3U,     2U,    (    NO_FLAGS   ),   RESULT_MEM,  false},
/* $85 */   {&Cpu::STA,     &Cpu::addrmode_zpg,   3U,     2U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $86 */   {&Cpu::STX,     &Cpu::addrmode_zpg,   3U,     2U,    (    NO_FLAGS   ),   RESULT_MEM,  false},
/* $87 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $88 */   {&Cpu::DEY,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $89 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $8A */   {&Cpu::TXA,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $8B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $8C */   {&Cpu::STY,     &Cpu::addrmode_abs,   4U,     2U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $8D */   {&Cpu::STA,     &Cpu::addrmode_abs,   4U,     3U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $8E */   {&Cpu::STX,     &Cpu::addrmode_abs,   4U,     3U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $8F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $90 */   {&Cpu::BCC,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $91 */   {&Cpu::STA,     &Cpu::addrmode_iny,   6U,     2U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $92 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $93 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $94 */   {&Cpu::STY,     &Cpu::addrmode_zpx,   4U,     2U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $95 */   {&Cpu::STA,     &Cpu::addrmode_zpx,   4U,     2U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $96 */   {&Cpu::STX,     &Cpu::addrmode_zpy,   4U,     2U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $97 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $98 */   {&Cpu::TYA,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $99 */   {&Cpu::STA,     &Cpu::addrmode_aby,   5U,     3U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $9A */   {&Cpu::TXS,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $9B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $9C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $9D */   {&Cpu::STA,     &Cpu::addrmode_abx,   5U,     3U,    (    NO_FLAGS   ),   RESULT_MEM , false},
/* $9E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $9F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $A0 */   {&Cpu::LDY,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $A1 */   {&Cpu::LDA,     &Cpu::addrmode_inx,   6U,     2U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $A2 */   {&Cpu::LDX,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $A3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $A4 */   {&Cpu::LDY,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $A5 */   {&Cpu::LDA,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $A6 */   {&Cpu::LDX,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $A7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $A8 */   {&Cpu::TAY,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $A9 */   {&Cpu::LDA,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $AA */   {&Cpu::TAX,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $AB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $AC */   {&Cpu::LDY,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $AD */   {&Cpu::LDA,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $AE */   {&Cpu::LDX,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $AF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $B0 */   {&Cpu::BCS,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $B1 */   {&Cpu::LDA,     &Cpu::addrmode_iny,   5U,     2U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $B2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $B3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $B4 */   {&Cpu::LDY,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $B5 */   {&Cpu::LDA,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $B6 */   {&Cpu::LDX,     &Cpu::addrmode_zpy,   4U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $B7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $B8 */   {&Cpu::CLV,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $B9 */   {&Cpu::LDA,     &Cpu::addrmode_aby,   4U,     3U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $BA */   {&Cpu::TSX,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $BB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $BC */   {&Cpu::LDY,     &Cpu::addrmode_abx,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $BD */   {&Cpu::LDA,     &Cpu::addrmode_abx,   4U,     3U,    (    F_N|F_Z    ),   RESULT_A   , false},
/* $BE */   {&Cpu::LDX,     &Cpu::addrmode_aby,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $BF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $C0 */   {&Cpu::CPY,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $C1 */   {&Cpu::CMP,     &Cpu::addrmode_inx,   6U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $C2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $C3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $C4 */   {&Cpu::CPY,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $C5 */   {&Cpu::CMP,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $C6 */   {&Cpu::DEC,     &Cpu::addrmode_zpg,   5U,     2U,    (    F_N|F_Z    ),   RESULT_MEM , false},
/* $C7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $C8 */   {&Cpu::INY,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $C9 */   {&Cpu::CMP,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $CA */   {&Cpu::DEX,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $CB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $CC */   {&Cpu::CPY,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $CD */   {&Cpu::CMP,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $CE */   {&Cpu::DEC,     &Cpu::addrmode_abs,   6U,     3U,    (    F_N|F_Z    ),   RESULT_MEM , false},
/* $CF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $D0 */   {&Cpu::BNE,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $D1 */   {&Cpu::CMP,     &Cpu::addrmode_iny,   5U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $D2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $D3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $D4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $D5 */   {&Cpu::CMP,     &Cpu::addrmode_zpx,   4U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $D6 */   {&Cpu::DEC,     &Cpu::addrmode_zpx,   6U,     2U,    (    F_N|F_Z    ),   RESULT_MEM , false},
/* $D7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $D8 */   {&Cpu::CLD,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $D9 */   {&Cpu::CMP,     &Cpu::addrmode_aby,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $DA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $DB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $DC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $DD */   {&Cpu::CMP,     &Cpu::addrmode_abx,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $DE */   {&Cpu::DEC,     &Cpu::addrmode_abx,   7U,     3U,    (    F_N|F_Z    ),   RESULT_MEM , false},
/* $DF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $E0 */   {&Cpu::CPX,     &Cpu::addrmode_imm,   2U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $E1 */   {&Cpu::SBC,     &Cpu::addrmode_inx,   6U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $E2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $E3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $E4 */   {&Cpu::CPX,     &Cpu::addrmode_zpg,   3U,     2U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $E5 */   {&Cpu::SBC,     &Cpu::addrmode_zpg,   3U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $E6 */   {&Cpu::INC,     &Cpu::addrmode_zpg,   5U,     2U,    (    F_N|F_Z    ),   RESULT_MEM , false},
/* $E7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $E8 */   {&Cpu::INX,     &Cpu::addrmode_imp,   2U,     1U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $E9 */   {&Cpu::SBC,     &Cpu::addrmode_imm,   2U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $EA */   {&Cpu::NOP,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $EB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $EC */   {&Cpu::CPX,     &Cpu::addrmode_abs,   4U,     3U,    (    F_N|F_Z    ),   RESULT_NONE, false},
/* $ED */   {&Cpu::SBC,     &Cpu::addrmode_abs,   4U,     3U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $EE */   {&Cpu::INC,     &Cpu::addrmode_abs,   6U,     3U,    (    F_N|F_Z    ),   RESULT_MEM , false},
/* $EF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $F0 */   {&Cpu::BEQ,     &Cpu::addrmode_imm,   2U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $F1 */   {&Cpu::SBC,     &Cpu::addrmode_iny,   5U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $F2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $F3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $F4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $F5 */   {&Cpu::SBC,     &Cpu::addrmode_zpx,   4U,     2U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $F6 */   {&Cpu::INC,     &Cpu::addrmode_zpx,   6U,     2U,    (    F_N|F_Z    ),   RESULT_MEM , false},
/* $F7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $F8 */   {&Cpu::SED,     &Cpu::addrmode_imp,   2U,     1U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $F9 */   {&Cpu::SBC,     &Cpu::addrmode_aby,   4U,     3U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $FA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $FB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $FC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false},
/* $FD */   {&Cpu::SBC,     &Cpu::addrmode_abx,   4U,     3U,    (F_N|F_V|F_Z|F_C),   RESULT_A   , false},
/* $FE */   {&Cpu::INC,     &Cpu::addrmode_abx,   7U,     3U,    (    F_N|F_Z    ),   RESULT_MEM , false},
/* $FF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   0U,     2U,    (    NO_FLAGS   ),   RESULT_NONE, false}
};

#endif
