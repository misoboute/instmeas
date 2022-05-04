#pragma once

#include "instmeas.h"

namespace instmeas
{

namespace funcs
{

namespace internal
{

INSTRUCTION_MEASUREMENT_DEFINE(XOR_R64_SAL_I_R64_IDIV64, 
    "xorq %%rdx,%%rdx\n\txorq $0x7fffffff,%%rax\n\tidiv %%rbx",
    "mov $25393642,%%rax\n\tmov $5039,%%rbx",
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(MOV2_I_R64_XOR_R_R64, 
    "mov $39916801,%%rax\n\tmov $5039,%%rbx\n\txor %%rdx,%%rdx", ,
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(XOR_R_R64, "xor %%rdx,%%rax", , , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_R64, "inc %%rdx", "xor %%rdx,%%rdx", , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_R64, "dec %%rdx", "xor %%rdx,%%rdx", , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_M64, 
    "incq %[mem1]", "movq $0,%[mem1]", , 8, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_M64, 
    "decq %[mem1]", "movq $0,%[mem1]", , 8, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_M32, 
    "incl %[mem1]", "movl $0,%[mem1]", , 4, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_M32, 
    "decl %[mem1]", "movl $0,%[mem1]", , 4, 1)

INSTRUCTION_MEASUREMENT_DEFINE(FLDPI, "fldpi", , , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(FLDPI_FSQRT_FSTP, 
    "fldpi\n\tfsqrt\n\tfstp %%st(0)", ,
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("st"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(FLDPI_FSTP, "fldpi\n\tfstp %%st(0)", ,
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("st"), 1, 1)

} // namespace internal

float IDIV_R64()
{
    return INSTRUCTION_MEASUREMENT_DO(XOR_R64_SAL_I_R64_IDIV64);
}

float XOR_R_R64()
{
    return INSTRUCTION_MEASUREMENT_DO(XOR_R_R64);
}

float MOV_R_I64()
{
    return (INSTRUCTION_MEASUREMENT_DO(MOV2_I_R64_XOR_R_R64) - 
        INSTRUCTION_MEASUREMENT_DO(XOR_R_R64)) / 2;
}

float INC_R64()
{
    return INSTRUCTION_MEASUREMENT_DO(INC_R64);
}

float DEC_R64()
{
    return INSTRUCTION_MEASUREMENT_DO(DEC_R64);
}

float INC_M64()
{
    return INSTRUCTION_MEASUREMENT_DO(INC_M64);
}

float DEC_M64()
{
    return INSTRUCTION_MEASUREMENT_DO(DEC_M64);
}

float INC_M32()
{
    return INSTRUCTION_MEASUREMENT_DO(INC_M32);
}

float DEC_M32()
{
    return INSTRUCTION_MEASUREMENT_DO(DEC_M32);
}

float FSQRT()
{
    return INSTRUCTION_MEASUREMENT_DO(FLDPI_FSQRT_FSTP) - 
        INSTRUCTION_MEASUREMENT_DO(FLDPI_FSTP);
}

} // namespace funcs

} // namespace instmeas
