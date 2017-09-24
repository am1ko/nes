#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H

#define NO_FLAGS    (0U)
#define NO_RESULT   (&Cpu::resultmode_none)

// ---------------------------------------------------------------------------------------------- //
const struct CpuInstruction Cpu::instruction_set[256] = {
// INSTR ---- OPCODE --------- ADDR MODE ----- CYCLES -------- FLAGS ---------  RESULT ---------- //
/* $00 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $01 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $02 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $03 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $04 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $05 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $06 */   {&Cpu::ASL,     &Cpu::addrmode_zpg,   2U,      (  F_C|F_Z|F_N  ),   &Cpu::resultmode_mem},
/* $07 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $08 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $09 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $0A */   {&Cpu::ASL_ACC, &Cpu::addrmode_imp,   2U,      (  F_C|F_Z|F_N  ),   &Cpu::resultmode_reg_a},
/* $0B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $0C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $0D */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $0E */   {&Cpu::ASL,     &Cpu::addrmode_abs,   2U,      (  F_C|F_Z|F_N  ),   &Cpu::resultmode_mem},
/* $0F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $10 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $11 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $12 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $13 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $14 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $15 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $16 */   {&Cpu::ASL,     &Cpu::addrmode_zpx,   2U,      (  F_C|F_Z|F_N  ),   &Cpu::resultmode_mem},
/* $17 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $18 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $19 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $1A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $1B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $1C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $1D */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $1E */   {&Cpu::ASL,     &Cpu::addrmode_abx,   2U,      (  F_C|F_Z|F_N  ),   &Cpu::resultmode_mem},
/* $1F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $20 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $21 */   {&Cpu::AND,     &Cpu::addrmode_inx,   2U,      (    F_Z|F_N    ),   &Cpu::resultmode_reg_a},
/* $22 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $23 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $24 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $25 */   {&Cpu::AND,     &Cpu::addrmode_zpg,   2U,      (    F_Z|F_N    ),   &Cpu::resultmode_reg_a},
/* $26 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $27 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $28 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $29 */   {&Cpu::AND,     &Cpu::addrmode_imm,   2U,      (    F_Z|F_N    ),   &Cpu::resultmode_reg_a},
/* $2A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $2B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $2C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $2D */   {&Cpu::AND,     &Cpu::addrmode_abs,   2U,      (    F_Z|F_N    ),   &Cpu::resultmode_reg_a},
/* $2E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $2F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $30 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $31 */   {&Cpu::AND,     &Cpu::addrmode_iny,   2U,      (    F_Z|F_N    ),   &Cpu::resultmode_reg_a},
/* $32 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $33 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $34 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $35 */   {&Cpu::AND,     &Cpu::addrmode_zpx,   2U,      (    F_Z|F_N    ),   &Cpu::resultmode_reg_a},
/* $36 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $37 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $38 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $39 */   {&Cpu::AND,     &Cpu::addrmode_aby,   2U,      (    F_Z|F_N    ),   &Cpu::resultmode_reg_a},
/* $3A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $3B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $3C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $3D */   {&Cpu::AND,     &Cpu::addrmode_abx,   2U,      (    F_Z|F_N    ),   &Cpu::resultmode_reg_a},
/* $3E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $3F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $40 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $41 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $42 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $43 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $44 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $45 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $46 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $47 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $48 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $49 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $4A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $4B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $4C */   {&Cpu::JMP,     &Cpu::addrmode_abs,   3U,      (    NO_FLAGS   ),   NO_RESULT},
/* $4D */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $4E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $4F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $50 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $51 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $52 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $53 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $54 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $55 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $56 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $57 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $58 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $59 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $5A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $5B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $5C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $5D */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $5E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $5F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $60 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $61 */   {&Cpu::ADC,     &Cpu::addrmode_inx,   2U,      (F_N|F_V|F_Z|F_C),   &Cpu::resultmode_reg_a},
/* $62 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $63 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $64 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $65 */   {&Cpu::ADC,     &Cpu::addrmode_zpg,   2U,      (F_N|F_V|F_Z|F_C),   &Cpu::resultmode_reg_a},
/* $66 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $67 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $68 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $69 */   {&Cpu::ADC,     &Cpu::addrmode_imm,   2U,      (F_N|F_V|F_Z|F_C),   &Cpu::resultmode_reg_a},
/* $6A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $6B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $6C */   {&Cpu::JMP,     &Cpu::addrmode_ind,   5U,      (    NO_FLAGS   ),   NO_RESULT},
/* $6D */   {&Cpu::ADC,     &Cpu::addrmode_abs,   2U,      (F_N|F_V|F_Z|F_C),   &Cpu::resultmode_reg_a},
/* $6E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $6F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $70 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $71 */   {&Cpu::ADC,     &Cpu::addrmode_iny,   2U,      (F_N|F_V|F_Z|F_C),   &Cpu::resultmode_reg_a},
/* $72 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $73 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $74 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $75 */   {&Cpu::ADC,     &Cpu::addrmode_zpx,   2U,      (F_N|F_V|F_Z|F_C),   &Cpu::resultmode_reg_a},
/* $76 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $77 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $78 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $79 */   {&Cpu::ADC,     &Cpu::addrmode_aby,   2U,      (    NO_FLAGS   ),   &Cpu::resultmode_reg_a},
/* $7A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $7B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $7C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $7D */   {&Cpu::ADC,     &Cpu::addrmode_abx,   2U,      (    NO_FLAGS   ),   &Cpu::resultmode_reg_a},
/* $7E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $7F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $80 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $81 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $82 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $83 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $84 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $85 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $86 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $87 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $88 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $89 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $8A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $8B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $8C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $8D */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $8E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $8F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $90 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $91 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $92 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $93 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $94 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $95 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $96 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $97 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $98 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $99 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $9A */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $9B */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $9C */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $9D */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $9E */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $9F */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $A0 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $A1 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $A2 */   {&Cpu::LDX,     &Cpu::addrmode_imm,   2U,      (    F_N|F_Z    ),   NO_RESULT},
/* $A3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $A4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $A5 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $A6 */   {&Cpu::LDX,     &Cpu::addrmode_zpg,   3U,      (    F_N|F_Z    ),   NO_RESULT},
/* $A7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $A8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $A9 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $AA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $AB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $AC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $AD */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $AE */   {&Cpu::LDX,     &Cpu::addrmode_abs,   4U,      (    F_N|F_Z    ),   NO_RESULT},
/* $AF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B0 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B1 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B5 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B6 */   {&Cpu::LDX,     &Cpu::addrmode_zpy,   4U,      (    F_N|F_Z    ),   NO_RESULT},
/* $B7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $B9 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $BA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $BB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $BC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $BD */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $BE */   {&Cpu::LDX,     &Cpu::addrmode_aby,   4U,      (    F_N|F_Z    ),   NO_RESULT},
/* $BF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C0 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C1 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C5 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C6 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $C9 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $CA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $CB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $CC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $CD */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $CE */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $CF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D0 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D1 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D5 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D6 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $D9 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $DA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $DB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $DC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $DD */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $DE */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $DF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E0 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E1 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E5 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E6 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $E9 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $EA */   {&Cpu::NOP,     &Cpu::addrmode_imp,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $EB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $EC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $ED */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $EE */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $EF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F0 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F1 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F2 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F3 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F4 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F5 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F6 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F7 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F8 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $F9 */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $FA */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $FB */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $FC */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $FD */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $FE */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT},
/* $FF */   {&Cpu::NOP,     &Cpu::addrmode_imm,   2U,      (    NO_FLAGS   ),   NO_RESULT}
};

#endif
