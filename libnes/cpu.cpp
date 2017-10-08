#include "imemory.h"
#include "cpu.h"
#include "instruction_set.h"

#define RESET_VECTOR_MSB_ADDR    (0xFFFDU)
#define RESET_VECTOR_LSB_ADDR    (0xFFFCU)

// ---------------------------------------------------------------------------------------------- //
Cpu::Cpu(IMemory& memory) : memory(memory), logger(0) {
    reset_registers();
    operand = 0U;
    acc_cached = context.sregs[A];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_imp() {
    return 0UL;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_imm() {
    context.PC++;
    return context.PC-1;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_ind() {
    uint16_t const addr = addrmode_abs();
    return memory.read(addr) | (memory.read(addr+1) << 8);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_zpg() {
    return memory.read(context.PC++);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_abs() {
    context.PC += 2U;
    return memory.read(context.PC - 2U) | (memory.read(context.PC - 1U) << 8);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_zpx() {
    return memory.read(context.PC++) + context.sregs[X];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_zpy() {
    return memory.read(context.PC++) + context.sregs[Y];
}

// ---------------------------------------------------------------------------------------------- //
// TODO(amiko): need to use X with carry?
uint16_t Cpu::addrmode_abx() {
    context.PC += 2U;
    return (memory.read(context.PC - 2U) | (memory.read(context.PC - 1) << 8)) + context.sregs[X];
}

// ---------------------------------------------------------------------------------------------- //
// TODO(amiko): need to use Y with carry?
uint16_t Cpu::addrmode_aby() {
    context.PC += 2U;
    return (memory.read(context.PC - 2U) | (memory.read(context.PC - 1U) << 8)) + context.sregs[Y];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_inx() {
    return memory.read(memory.read(context.PC++) + context.sregs[X]);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::addrmode_iny() {
    return memory.read(memory.read(context.PC++)) + context.sregs[Y];
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::resultmode_none(uint16_t addr, uint8_t result) {

}

// ---------------------------------------------------------------------------------------------- //
void Cpu::resultmode_mem(uint16_t addr, uint8_t result) {
    memory.write(addr, result);
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::resultmode_reg_a(uint16_t addr, uint8_t result) {
    context.sregs[A] = result;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::ADC(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = memory.read(operand_addr);
    return context.sregs[A] + operand + (context.P & F_C);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::AND(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = memory.read(operand_addr);
    return context.sregs[A] & operand;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::ASL(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = memory.read(operand_addr);
    return operand << 1;
}

// ---------------------------------------------------------------------------------------------- //
// TODO(amiko): use parameter (bool operand_in_acc = false) instead?
uint16_t Cpu::ASL_ACC(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = context.sregs[A];
    return operand << 1;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::NOP(uint16_t operand_addr, uint8_t &extra_cycles) {
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::JMP(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.PC = operand_addr;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::LDX(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.sregs[X] = memory.read(operand_addr);
    return context.sregs[X];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::STX(uint16_t operand_addr, uint8_t &extra_cycles) {
    memory.write(operand_addr, context.sregs[X]);
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::JSR(uint16_t operand_addr, uint8_t &extra_cycles) {
    uint16_t const next_addr_minus_one = context.PC - 1U;
    memory.write(0x100U + context.SP--, (next_addr_minus_one >> 8) & 0xFF);
    memory.write(0x100U + context.SP--, next_addr_minus_one        & 0xFF);
    context.PC = operand_addr;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::RTS(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.PC =  memory.read(0x100U + ++context.SP) + 1U
               + (memory.read(0x100U + ++context.SP) << 8);
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::PHP(uint16_t operand_addr, uint8_t &extra_cycles) {
    memory.write(0x100U + context.SP--, (context.P | F_B));
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::PLP(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.P = memory.read(0x100U + ++context.SP);
    context.P &= ~(F_B);      // bit 4 is not a normal status flag, ignore it
    context.P |= 1U << 5;     // bit 5 is always set
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::PLA(uint16_t operand_addr, uint8_t &extra_cycles) {
    return memory.read(0x100U + ++context.SP);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::PHA(uint16_t operand_addr, uint8_t &extra_cycles) {
    memory.write(0x100U + context.SP--, context.sregs[A]);
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::SEC(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.P |= F_C;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::CLC(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.P &= ~(F_C);
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::SEI(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.P |= F_I;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::SED(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.P |= F_D;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::CLD(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.P &= ~(F_D);
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::CLV(uint16_t operand_addr, uint8_t &extra_cycles) {
    context.P &= ~(F_V);
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
// TODO(amiko): check cpu cycle count with this instruction
uint16_t Cpu::BCS(uint16_t operand_addr, uint8_t &extra_cycles) {
    int8_t const operand = (int8_t)memory.read(operand_addr);
    if (context.P & F_C) {
        branch(operand, extra_cycles);
    }

    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BCC(uint16_t operand_addr, uint8_t &extra_cycles) {
    int8_t const operand = (int8_t)memory.read(operand_addr);
    if (!(context.P & F_C)) {
        branch(operand, extra_cycles);
    }

    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BEQ(uint16_t operand_addr, uint8_t &extra_cycles) {
    int8_t const operand = (int8_t)memory.read(operand_addr);
    if (context.P & F_Z) {
        branch(operand, extra_cycles);
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BNE(uint16_t operand_addr, uint8_t &extra_cycles) {
    int8_t const operand = (int8_t)memory.read(operand_addr);
    if (!(context.P & F_Z)) {
        branch(operand, extra_cycles);
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BVS(uint16_t operand_addr, uint8_t &extra_cycles) {
    int8_t const operand = (int8_t)memory.read(operand_addr);
    if (context.P & F_V) {
        branch(operand, extra_cycles);
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BVC(uint16_t operand_addr, uint8_t &extra_cycles) {
    int8_t const operand = (int8_t)memory.read(operand_addr);
    if (!(context.P & F_V)) {
        branch(operand, extra_cycles);
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BMI(uint16_t operand_addr, uint8_t &extra_cycles) {
    int8_t const operand = (int8_t)memory.read(operand_addr);
    if (context.P & F_N) {
        branch(operand, extra_cycles);
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BPL(uint16_t operand_addr, uint8_t &extra_cycles) {
    int8_t const operand = (int8_t)memory.read(operand_addr);
    if (!(context.P & F_N)) {
        branch(operand, extra_cycles);
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::LDA(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = memory.read(operand_addr);
    return operand;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::STA(uint16_t operand_addr, uint8_t &extra_cycles) {
    return context.sregs[A];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BIT(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = memory.read(operand_addr);
    uint16_t const ret =  context.sregs[A] & operand;

    context.P &= ~(F_N | F_V);
    context.P |= (operand & (F_N | F_V));

    return ret;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::CMP(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = memory.read(operand_addr);
    uint16_t const ret = context.sregs[A] - operand;

    if (ret < 256U) { context.P |= F_C; } else { context.P &= ~(F_C); }

    return ret;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::ORA(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = memory.read(operand_addr);
    return context.sregs[A] | operand;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::EOR(uint16_t operand_addr, uint8_t &extra_cycles) {
    operand = memory.read(operand_addr);
    return context.sregs[A] ^ operand;
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::update_flags(uint16_t result, uint8_t mask) {
    // --- CARRY (UNSIGNED RESULT INVALID) ------------------------------------------------------ //
    if (mask & F_C) {
        if (result > 0xFFU) {
            context.P |= F_C;
            result %= 256U;
        }
        else {
            context.P &= ~(F_C);
        }
    }

    // --- ZERO --------------------------------------------------------------------------------- //
    if (mask & F_Z) {
        if ((result) == 0U) {
            context.P |= F_Z;
        }
        else {
            context.P &= ~(F_Z);
        }
    }

    // --- OVERFLOW (SIGNED RESULT INVALID)------------------------------------------------------ //
    // Overflow is set if: Positive + Positive = Negative or Negative + Negative = Positive
    if (mask & F_V) {
        if ((acc_cached ^ result) & (operand ^ result) & 0x80U) {
            context.P |= F_V;
        }
        else {
            context.P &= ~(F_V);
        }
    }

    // --- NEGATIVE ----------------------------------------------------------------------------- //
    if (mask & F_N) {
        if (result & 0x80U) {
            context.P |= F_N;
        }
        else {
            context.P &= ~(F_N);
        }
    }
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::branch(int8_t op, uint8_t &extra_cycles) {
    extra_cycles = 1U;
    if (op >= 0) {
        context.PC += op;
    }
    else{
        context.PC += (op-2U);
    }
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::reset_registers() {
    context.P = (1U << 5) | F_I;
    context.SP = 0xFDU;
    context.sregs[A] = 0U;
    context.sregs[X] = 0U;
    context.sregs[Y] = 0U;
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::set_logger(ICpuLogger * logger) {
    this->logger = logger;
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::log(uint16_t pc, uint8_t len, uint8_t cycles) {
    if (logger) {
        uint8_t instr_buf[3] = { memory.read(pc), 0U, 0U };
        for (int i = 1; i < len; i++) { instr_buf[i] = memory.read(pc+i); }
        logger->log(instr_buf, len, pc, cycles, &context);
    }
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::reset() {
    reset_registers();
    context.PC = memory.read(RESET_VECTOR_LSB_ADDR) | (memory.read(RESET_VECTOR_MSB_ADDR) << 8);
}

// ---------------------------------------------------------------------------------------------- //
unsigned Cpu::tick() {
    uint16_t const pc = context.PC;
    uint8_t extra_cycles = 0U;
    acc_cached = context.sregs[A];

    // --- FETCH & DECODE INSTRUCTION ------------- //
    struct CpuInstruction const * instr = &instruction_set[memory.read(context.PC++)];

    // --- LOG ------------------------------------ //
    log(pc, instr->bytes, instr->cycles);

    // --- FETCH OPERAND ADDRESS ------------------ //
    uint16_t const addr = (*this.*instr->addrmode_handler)();

    // --- EXECUTE -------------------------------- //
    uint16_t const result = (*this.*instr->instr_executor)(addr, extra_cycles);

    // --- UPDATE CPU STATE ----------------------- //
    update_flags(result, instr->flags);

    // --- STORE RESULT --------------------------- //
    (*this.*instr->result_handler)(addr, result % 256U);

    return instr->cycles + extra_cycles;
}
