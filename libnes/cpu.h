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
    uint16_t ADC(uint16_t param_addr);
    uint16_t AND(uint16_t param_addr);
    uint16_t ASL(uint16_t param_addr);
    uint16_t ASL_ACC(uint16_t param_addr);
    uint16_t NOP(uint16_t param_addr);
    uint16_t JMP(uint16_t param_addr);
    uint16_t LDX(uint16_t param_addr);
    uint16_t STX(uint16_t param_addr);
    uint16_t JSR(uint16_t param_addr);
    uint16_t SEC(uint16_t param_addr);
    uint16_t BCS(uint16_t param_addr);
    uint16_t BCC(uint16_t param_addr);
    uint16_t BEQ(uint16_t param_addr);
    uint16_t BNE(uint16_t param_addr);
    uint16_t CLC(uint16_t param_addr);
    uint16_t LDA(uint16_t param_addr);
    uint16_t STA(uint16_t param_addr);
    // --- OTHER -------------------------------------------------------------------------------- //
    void branch(int8_t op);
    void log(uint16_t pc, uint8_t len, uint8_t cycles);
    void update_flags(uint16_t result, uint8_t mask);
    void reset_registers();
public:
    CpuContext context;
    explicit Cpu(IMemory& memory);
    void reset();
    unsigned tick();
    void set_logger(ICpuLogger * logger);
};

struct CpuInstruction {
    uint16_t (Cpu::*instr_executor)(uint16_t);
    uint16_t (Cpu::*addrmode_handler)();
    uint8_t cycles;
    uint8_t bytes;
    uint8_t flags;
    void (Cpu::*result_handler)(uint16_t, uint8_t);
};

#endif
