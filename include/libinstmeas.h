#pragma once

#include "instmeas.h"

namespace instmeas
{

namespace funcs
{

namespace internal
{

INSTRUCTION_MEASUREMENT_DEFINE(XOR_I32_R64_XOR_R64_IDIV64, 
    "xorq %%rdx,%%rdx\n\txorq $0x7fffffff,%%rax\n\tidiv %%rbx",
    "mov $25393642,%%rax\n\tmov $5039,%%rbx", , 
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(MOV_I_R64, 
    "mov $0x8d13fd2583b74e96,%%rax", , , , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(XOR_R64, 
    "xorq %%rdx,%%rdx", "movq $0xbbbbbbbbbbbbbbbb,%%rdx", , , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(XOR_I32_R64, 
    "xorq $0x7fffffff,%%rax", "movq $0xbbbbbbbbbbbbbbbb,%%rax", , , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_R64, "inc %%rbx", "xor %%rbx,%%rbx", , 
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_R64, 
    "dec %%rbx", "movq $0xffffffff,%%rbx", , 
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_M64, 
    "incq %[mem1]", "movq $0,%[mem1]", , , 8, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_M64, 
    "decq %[mem1]", "movq $0x7fffffff,%[mem1]", , , 8, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_M32, 
    "incl %[mem1]", "movl $0,%[mem1]", , , 4, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_M32, 
    "decl %[mem1]", "movl $0x7fffffff,%[mem1]", , , 4, 1)

INSTRUCTION_MEASUREMENT_DEFINE(FMUL_ST_ST, "fmul %%st(0),%%st(1)", 
    "movl $0x3f8020c5,%[mem1]\n\tfldl %[mem1]\n\tfldpi", ,
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("st"), 4, 1)

INSTRUCTION_MEASUREMENT_DEFINE(FLDPI, "fldpi", , , , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(FLDPI_FSQRT_FSTP, 
    "fldpi\n\tfsqrt\n\tfstp %%st(0)", , ,
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("st"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(FLDPI_FSTP, "fldpi\n\tfstp %%st(0)", , ,
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("st"), 1, 1)

} // namespace internal

float IDIV_R64()
{
    return INSTRUCTION_MEASUREMENT_DO(XOR_I32_R64_XOR_R64_IDIV64) -
        INSTRUCTION_MEASUREMENT_DO(XOR_R64) -
        INSTRUCTION_MEASUREMENT_DO(XOR_I32_R64);
}

float XOR_R64()
{
    return INSTRUCTION_MEASUREMENT_DO(XOR_R64);
}

float XOR_I32_R64()
{
    return INSTRUCTION_MEASUREMENT_DO(XOR_I32_R64);
}

float MOV_R_I64()
{
    return INSTRUCTION_MEASUREMENT_DO(MOV_I_R64);
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

float FMUL_ST_ST()
{
    return INSTRUCTION_MEASUREMENT_DO(FMUL_ST_ST);
}

float FSQRT()
{
    return INSTRUCTION_MEASUREMENT_DO(FLDPI_FSQRT_FSTP) - 
        INSTRUCTION_MEASUREMENT_DO(FLDPI_FSTP);
}

} // namespace funcs

} // namespace instmeas
