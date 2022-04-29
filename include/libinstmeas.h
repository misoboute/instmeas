#pragma once

#include "instmeas.h"

namespace instmeas
{

namespace funcs
{

namespace internal
{

INSTRUCTION_MEASUREMENT_DEFINE(MOV2_I_R64_XOR_R_R64_IDIV64, 
    "mov $39916801,%%rax\n\tmov $5039,%%rbx\n\txor %%rdx,%%rdx\n\tidiv %%rbx",
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(MOV2_I_R64_XOR_R_R64, 
    "mov $39916801,%%rax\n\tmov $5039,%%rbx\n\txor %%rdx,%%rdx",
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"), 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(XOR_R_R64, "xor %%rdx,%%rdx", , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_R64, "inc %%rdx", , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_R64, "dec %%rdx", , 1, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_M64, "incq %[mem1]", , 8, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_M64, "decq %[mem1]", , 8, 1)

INSTRUCTION_MEASUREMENT_DEFINE(INC_M32, "incl %[mem1]", , 4, 1)

INSTRUCTION_MEASUREMENT_DEFINE(DEC_M32, "decl %[mem1]", , 4, 1)

} // namespace internal

float IDIV_R64()
{
    return INSTRUCTION_MEASUREMENT_DO(MOV2_I_R64_XOR_R_R64_IDIV64) - 
        INSTRUCTION_MEASUREMENT_DO(MOV2_I_R64_XOR_R_R64);
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

} // namespace funcs

} // namespace instmeas