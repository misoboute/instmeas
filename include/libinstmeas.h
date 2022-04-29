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
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"))

INSTRUCTION_MEASUREMENT_DEFINE(MOV2_I_R64_XOR_R_R64, 
    "mov $39916801,%%rax\n\tmov $5039,%%rbx\n\txor %%rdx,%%rdx",
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"))

INSTRUCTION_MEASUREMENT_DEFINE(XOR_R_R64, "xor %%rdx,%%rdx", )

INSTRUCTION_MEASUREMENT_DEFINE(INC_R64, "inc %%rdx", )

INSTRUCTION_MEASUREMENT_DEFINE(DEC_R64, "dec %%rdx", )

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

} // namespace funcs

} // namespace instmeas