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
class Cpu
{
    static const struct CpuInstruction instruction_set[256];
    IMemory & memory;
    uint16_t addr;
    // --- RESULT STORE MODES-------------------------------------------------------------------- //
    void resultmode_none(uint8_t result);
    void resultmode_mem(uint8_t result);
    void resultmode_reg_a(uint8_t result);
    // --- ADDRESSING MODES --------------------------------------------------------------------- //
    uint8_t addrmode_acc();
    uint8_t addrmode_imp();
    uint8_t addrmode_imm();
    uint8_t addrmode_zpg();
    uint8_t addrmode_abs();
    uint8_t addrmode_zpx();
    uint8_t addrmode_abx();
    uint8_t addrmode_aby();
    uint8_t addrmode_inx();
    uint8_t addrmode_iny();
    // --- INSTRUCTIONS ------------------------------------------------------------------------- //
    uint16_t ADC(uint8_t param) const;
    uint16_t AND(uint8_t param) const;
    uint16_t ASL(uint8_t param) const;
    uint16_t NOP(uint8_t param) const;
    // --- OTHER -------------------------------------------------------------------------------- //
    void update_flags(uint16_t result, uint8_t mask);;
public:
    CpuContext context;
    Cpu(IMemory& memory);
    void reset();
    void tick();
};

struct CpuInstruction {
    uint16_t (Cpu::*instr_executor)(uint8_t) const;
    uint8_t (Cpu::*addrmode_handler)();
    uint8_t cycles;
    uint8_t flags;
    void (Cpu::*result_handler)(uint8_t);
};

#endif
