#include "imemory.h"
#include "cpu.h"
#include "instruction_set.h"

#define RESET_VECTOR_MSB_ADDR    (0xFFFDU)
#define RESET_VECTOR_LSB_ADDR    (0xFFFCU)

// ---------------------------------------------------------------------------------------------- //
Cpu::Cpu(IMemory& memory) : memory(memory), logger(0) {
    reset_registers();
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
uint16_t Cpu::ADC(uint16_t param_addr) {
    uint8_t const param = memory.read(param_addr);
    return context.sregs[A] + param + (context.P & F_C);
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::AND(uint16_t param_addr) {
    uint8_t const param = memory.read(param_addr);
    return context.sregs[A] & param;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::ASL(uint16_t param_addr) {
    uint8_t const param = memory.read(param_addr);
    return param << 1;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::ASL_ACC(uint16_t param_addr) {
    uint8_t const param = context.sregs[A];
    return param << 1;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::NOP(uint16_t param_addr) {
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::JMP(uint16_t param_addr) {
    context.PC = param_addr;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::LDX(uint16_t param_addr) {
    context.sregs[X] = memory.read(param_addr);
    return context.sregs[X];
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::STX(uint16_t param_addr) {
    memory.write(param_addr, context.sregs[X]);
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::JSR(uint16_t param_addr) {
    uint16_t const next_addr_minus_one = context.PC - 1U;
    memory.write(0x100U + context.SP--, (next_addr_minus_one >> 8) & 0xFF);
    memory.write(0x100U + context.SP--, next_addr_minus_one        & 0xFF);
    context.PC = param_addr;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::SEC(uint16_t param_addr) {
    context.P |= F_C;
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::CLC(uint16_t param_addr) {
    context.P &= ~(F_C);
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
// TODO(amiko): check cpu cycle count with this instruction
uint16_t Cpu::BCS(uint16_t param_addr) {
    int8_t const operand = (int8_t)memory.read(param_addr);
    if (context.P & F_C) {
        branch(operand);
    }

    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BCC(uint16_t param_addr) {
    int8_t const operand = (int8_t)memory.read(param_addr);
    if (!(context.P & F_C)) {
        branch(operand);
    }

    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BEQ(uint16_t param_addr) {
    int8_t const operand = (int8_t)memory.read(param_addr);
    if (context.P & F_Z) {
        branch(operand);
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::BNE(uint16_t param_addr) {
    int8_t const operand = (int8_t)memory.read(param_addr);
    if (!(context.P & F_Z)) {
        branch(operand);
    }
    return 0U;
}

// ---------------------------------------------------------------------------------------------- //
uint16_t Cpu::LDA(uint16_t param_addr) {
    uint8_t const param = memory.read(param_addr);
    return param;
}

// ---------------------------------------------------------------------------------------------- //
void Cpu::update_flags(uint16_t result, uint8_t mask) {
    // --- CARRY --- //
    if (mask & F_C) {
        if (result > 0xFFU) {
            context.P |= F_C;
            result %= 256U;
        }
        else {
            context.P &= ~(F_C);
        }
    }

    // --- ZERO --- //
    if (mask & F_Z) {
        if ((result) == 0U) {
            context.P |= F_Z;
        }
        else {
            context.P &= ~(F_Z);
        }
    }

    // --- OVERFLOW --- //
    if (mask & F_V) {
        if ((result & 0x80U) != (context.sregs[A] & 0x80U)) {
            context.P |= F_V;
        }
        else {
            context.P &= ~(F_V);
        }
    }

    // --- NEGATIVE --- //
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
void Cpu::branch(int8_t op) {
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

    // --- FETCH & DECODE INSTRUCTION ------------- //
    struct CpuInstruction const * instr = &instruction_set[memory.read(context.PC++)];

    // --- LOG ------------------------------------ //
    log(pc, instr->bytes, instr->cycles);

    // --- FETCH OPERAND ADDRESS ------------------ //
    uint16_t const addr = (*this.*instr->addrmode_handler)();

    // --- EXECUTE -------------------------------- //
    uint16_t const result = (*this.*instr->instr_executor)(addr);

    // --- UPDATE CPU STATE ----------------------- //
    update_flags(result, instr->flags);

    // --- STORE RESULT --------------------------- //
    (*this.*instr->result_handler)(addr, result % 256U);

    return instr->cycles;
}
