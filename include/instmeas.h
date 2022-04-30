#pragma once

#include <cstdint>

#define INSTRUCTION_MEASUREMENT_MARK_START  "\t" \
    "mfence          \n\t"   \
    "lfence          \n\t"   \
    "rdtsc           \n\t"   \
    "lfence          \n\t"   \
    "shl $32, %%rdx  \n\t"   \
    "or %%rax, %%rdx \n\t"   \
    "mov %%rdx, %0   \n\t"

#define INSTRUCTION_MEASUREMENT_MARK_END  "\t" \
    "mfence          \n\t"   \
    "lfence          \n\t"   \
    "rdtsc           \n\t"   \
    "lfence          \n\t"   \
    "shl $32, %%rdx  \n\t"   \
    "or %%rax, %%rdx \n\t"   \
    "xchg %%rdx, %0  \n\t"   \
    "sub %%rdx, %0   \n\t"

#define INSTRUCTION_MEASUREMENT_REPEAT_4(INST)   \
    INST "\n\t" INST "\n\t" INST "\n\t" INST "\n\t" 

#define INSTRUCTION_MEASUREMENT_REPEAT_16(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_4(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_4(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_4(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_4(INST)

#define INSTRUCTION_MEASUREMENT_REPEAT_64(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_16(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_16(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_16(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_16(INST)

#define INSTRUCTION_MEASUREMENT_REPEAT_256(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_64(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_64(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_64(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_64(INST)

#define INSTRUCTION_MEASUREMENT_REPEAT_1024(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_256(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_256(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_256(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_256(INST)

#define INSTRUCTION_MEASUREMENT_REPEAT_4K(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_1024(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_1024(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_1024(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_1024(INST)

#define INSTRUCTION_MEASUREMENT_REPEAT_16K(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_4K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_4K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_4K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_4K(INST)

#define INSTRUCTION_MEASUREMENT_REPEAT_64K(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_16K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_16K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_16K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_16K(INST)

#define INSTRUCTION_MEASUREMENT_REPEAT_256K(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_64K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_64K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_64K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_64K(INST)

#define INSTRUCTION_MEASUREMENT_REPEAT_1024K(INST)   \
    INSTRUCTION_MEASUREMENT_REPEAT_256K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_256K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_256K(INST) \
    INSTRUCTION_MEASUREMENT_REPEAT_256K(INST)

// By default each instruction listing is repeated 1024 before being 
// surrounded by timing markers. Then the measured time is divided by 1024
// to compute the average time for each single run of the listing.
// To disable this repetition, define this macro before including the header.
#ifdef INSTRUCTION_MEASUREMENT_NO_REPEAT_LISTING
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) X "\n\t"
#define INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS 1
#else
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) \
    INSTRUCTION_MEASUREMENT_REPEAT_16K(X)
#define INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS (1024 * 16)
#endif

#ifndef INSTRUCTION_MEASUREMENT_NUM_RUN_REPS
#define INSTRUCTION_MEASUREMENT_NUM_RUN_REPS (16 * 1024)
#endif

#define INSTRUCTION_MEASUREMENT_DEFINE(NAME, INST_TEMPLATE, CLOBBER,    \
    MEMSIZE1, MEMSIZE2)                                                 \
float InstructionMeasurementFunc##NAME()                                \
{                                                                       \
    constexpr const int64_t numMeasurements =                           \
        INSTRUCTION_MEASUREMENT_NUM_RUN_REPS;                           \
    int64_t totalTicks = 0;                                             \
    char mem1[MEMSIZE1] { 0 };                                          \
    char mem2[MEMSIZE2] { 0 };                                          \
    for (auto i = 0; i < numMeasurements; ++i)                          \
    {                                                                   \
        uint64_t ticks = 0;                                             \
        asm volatile (                                                  \
            INSTRUCTION_MEASUREMENT_MARK_START                          \
            INSTRUCTION_MEASUREMENT_MARK_END                            \
            : "=r" (ticks)                                              \
            :                                                           \
            : "rax", "rdx");                                            \
        totalTicks -= ticks;                                            \
        asm volatile (                                                  \
            INSTRUCTION_MEASUREMENT_MARK_START                          \
            /* Instructions to measure start here */                    \
            INSTRUCTION_MEASUREMENT_INSERT_LISTING(INST_TEMPLATE)       \
            /* Instructions to measure end here */                      \
            INSTRUCTION_MEASUREMENT_MARK_END                            \
            : "=r" (ticks), [mem1] "=m" (mem1), [mem2] "=m" (mem2)      \
            : [addrMem1] "r" (&mem1), [addrMem2] "r" (&mem2)            \
            : "rax", "rdx" CLOBBER);                                    \
        totalTicks += ticks;                                            \
    }                                                                   \
    return static_cast<float>(totalTicks) / numMeasurements /           \
        INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS;                       \
}

#define INSTRUCTION_MEASUREMENT_DO(NAME)   \
    ::instmeas::funcs::internal::InstructionMeasurementFunc##NAME()

#define INSTRUCTION_MEASUREMENT_REG_CLOBBER(...) , __VA_ARGS__
