#ifndef CPU_H
#define CPU_H

#include <cstdbool>
#include <cstdint>

class IMemory;

// ---------------------------------------------------------------------------------------------- //
// Status Register (SR, P) flags
#define F_C   (1U << 0)
#define F_Z   (1U << 1)
#define F_I   (1U << 2)
#define F_D   (1U << 3)
#define F_B   (1U << 4)
// ---- Unused ----- //
#define F_V   (1U << 6)
#define F_N   (1U << 7)

// ---------------------------------------------------------------------------------------------- //
// CPU special register indexes
enum {
    A = 0, X, Y,
};

// ---------------------------------------------------------------------------------------------- //
struct CpuContext {
    uint8_t sregs[3];   // A, X, Y
    uint8_t P;
    uint8_t SP;
    uint16_t PC;
};

// ---------------------------------------------------------------------------------------------- //
class ICpuLogger {
public:
    virtual void log(uint8_t const * instr, uint8_t bytes, uint16_t instr_addr, uint8_t cycles,
                     struct CpuContext const * const context) = 0;
};

// ---------------------------------------------------------------------------------------------- //
class Cpu
{
    static const struct CpuInstruction instruction_set[256];
    ICpuLogger * logger;
    IMemory & memory;
    // --- CACHED VALUES ------------------------------------------------------------------------ //
    uint8_t operand;
    uint8_t acc_cached;
    // --- RESULT STORE MODES-------------------------------------------------------------------- //
    void resultmode_none(uint16_t addr, uint8_t result);
    void resultmode_mem(uint16_t addr, uint8_t result);
    void resultmode_reg_a(uint16_t addr, uint8_t result);
    // --- ADDRESSING MODES --------------------------------------------------------------------- //
    uint16_t addrmode_imp();
    uint16_t addrmode_imm();
    uint16_t addrmode_ind();
    uint16_t addrmode_zpg();
    uint16_t addrmode_abs();
    uint16_t addrmode_zpx();
    uint16_t addrmode_zpy();
    uint16_t addrmode_abx();
    uint16_t addrmode_aby();
    uint16_t addrmode_inx();
    uint16_t addrmode_iny();
    // --- INSTRUCTIONS ------------------------------------------------------------------------- //
    uint16_t ADC(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t AND(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t ASL(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BCC(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BCS(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BEQ(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BIT(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BMI(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BNE(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BPL(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
//  uint16_t BRK(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BVC(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t BVS(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t CLC(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t CLD(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
//  uint16_t CLI(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t CLV(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t CMP(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t CPX(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t CPY(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
//  uint16_t DEC(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t DEX(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t DEY(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t EOR(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
//  uint16_t INC(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t INX(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t INY(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t JMP(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t JSR(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t LDA(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t LDX(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t LDY(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t LSR(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t NOP(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t ORA(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t PHA(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t PHP(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t PLA(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t PLP(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
//  uint16_t ROL(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t ROR(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t RTI(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t RTS(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t SBC(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t SEC(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t SED(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t SEI(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t STA(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t STX(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
//  uint16_t STY(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t TAX(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t TAY(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t TSX(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t TXA(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t TXS(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    uint16_t TYA(uint16_t operand_addr, uint8_t &extra_cycles, bool op_in_acc);
    // --- OTHER -------------------------------------------------------------------------------- //
    void    branch(int8_t op, uint8_t &extra_cycles);
    uint8_t compare(uint16_t operand_addr, uint8_t reg);
    void    log(uint16_t pc, uint8_t len, uint8_t cycles);
    void    update_flags(uint16_t result, uint8_t mask);
    void    reset_registers();
public:
    CpuContext context;
    explicit Cpu(IMemory& memory);
    void reset();
    unsigned tick();
    void set_logger(ICpuLogger * logger);
};

struct CpuInstruction {
    uint16_t (Cpu::*instr_executor)(uint16_t, uint8_t&, bool);
    uint16_t (Cpu::*addrmode_handler)();
    uint8_t cycles;
    uint8_t bytes;
    uint8_t flags;
    void (Cpu::*result_handler)(uint16_t, uint8_t);
    bool op_in_acc;
};

#endif
