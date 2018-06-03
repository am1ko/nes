#ifndef MOCK_CPU_INTERRUPT_H
#define MOCK_CPU_INTERRUPT_H

#include "gmock/gmock.h"
#include "cpu_interrupt.h"

class MockCpuInterrupt: public CpuInterrupt
{
public:
    MOCK_METHOD1(set_interrupt_pending, void(enum InterruptSource source));
};

#endif