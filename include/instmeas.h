#pragma once

#include <cstdint>

#define IM_REP1(X) X "\n\t"
#define IM_REP2(X) IM_REP1(X) IM_REP1(X)
#define IM_REP4(X) IM_REP2(X) IM_REP2(X)
#define IM_REP8(X) IM_REP4(X) IM_REP4(X)
#define IM_REP16(X) IM_REP8(X) IM_REP8(X)
#define IM_REP32(X) IM_REP16(X) IM_REP16(X)
#define IM_REP64(X) IM_REP32(X) IM_REP32(X)
#define IM_REP128(X) IM_REP64(X) IM_REP64(X)
#define IM_REP256(X) IM_REP128(X) IM_REP128(X)
#define IM_REP512(X) IM_REP256(X) IM_REP256(X)
#define IM_REP1K(X) IM_REP512(X) IM_REP512(X)
#define IM_REP2K(X) IM_REP1K(X) IM_REP1K(X)
#define IM_REP4K(X) IM_REP2K(X) IM_REP2K(X)
#define IM_REP8K(X) IM_REP4K(X) IM_REP4K(X)
#define IM_REP16K(X) IM_REP8K(X) IM_REP8K(X)
#define IM_REP32K(X) IM_REP16K(X) IM_REP16K(X)
#define IM_REP64K(X) IM_REP32K(X) IM_REP32K(X)
#define IM_REP128K(X) IM_REP64K(X) IM_REP64K(X)
#define IM_REP256K(X) IM_REP128K(X) IM_REP128K(X)
#define IM_REP512K(X) IM_REP256K(X) IM_REP256K(X)
#define IM_REP1M(X) IM_REP512K(X) IM_REP512K(X)

// By default each instruction listing is repeated 2^12 times before being
// surrounded by timing markers. Then the measured time is divided by 1024
// to compute the average time for each single run of the listing.
// To disable this repetition, define this macro before including the header.
#ifndef INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS
#define INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS (1 << 12)
#endif

#if INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP1(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 1
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP2(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 2
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP4(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 3
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP8(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 4
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP16(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 5
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP32(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 6
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP64(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 7
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP128(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 8
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP256(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 9
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP512(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 10
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP1K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 11
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP2K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 12
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP4K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 13
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP8K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 14
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP16K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 15
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP32K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 16
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP64K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 17
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP128K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 18
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP256K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 19
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP512K(X)
#elif INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS == 1 << 20
#define INSTRUCTION_MEASUREMENT_INSERT_LISTING(X) IM_REP1M(X)
#else
#error "Invalid value for INSTRUCTION_MEASUREMENT_REPEAT_LISTING acceptable \
    values are (2^p) where p >= 0 && p <= 20"
#endif

#ifndef INSTRUCTION_MEASUREMENT_NUM_RUN_REPS
#define INSTRUCTION_MEASUREMENT_NUM_RUN_REPS (1 << 12)
#endif

#define INSTRUCTION_MEASUREMENT_MARK_START  \
    "mfence                     \n\t"   \
    "lfence                     \n\t"   \
    "rdtsc                      \n\t"   \
    "lfence                     \n\t"   \
    "shl $32, %%rdx             \n\t"   \
    "or %%rax, %%rdx            \n\t"   \
    "mov %%rdx, %[ticks]        \n\t"

#define INSTRUCTION_MEASUREMENT_MARK_END    \
    "mfence                     \n\t"   \
    "lfence                     \n\t"   \
    "rdtsc                      \n\t"   \
    "lfence                     \n\t"   \
    "shl $32, %%rdx             \n\t"   \
    "or %%rax, %%rdx            \n\t"   \
    "xchg %%rdx, %[ticks]       \n\t"   \
    "sub %%rdx, %[ticks]        \n\t"

#define INSTRUCTION_MEASUREMENT_DEFINE(NAME, INST_TEMPLATE, INIT, CLOBBER,     \
    MEMSIZE1, MEMSIZE2)                                                        \
float InstructionMeasurementFunc##NAME()                                       \
{                                                                              \
    int64_t totalTicks = 0;                                                    \
    int64_t ticks = 0;                                                         \
    int64_t counter = INSTRUCTION_MEASUREMENT_NUM_RUN_REPS;                    \
    alignas(16) char mem1[MEMSIZE1] { 0 };                                     \
    alignas(16) char mem2[MEMSIZE2] { 0 };                                     \
    asm volatile (                                                             \
        INIT "\n"                                                              \
        "%=:\t"                                                                \
        INSTRUCTION_MEASUREMENT_MARK_START                                     \
        INSTRUCTION_MEASUREMENT_INSERT_LISTING(INST_TEMPLATE)                  \
        INSTRUCTION_MEASUREMENT_MARK_END                                       \
        "add %[ticks], %[totalTicks]        \n\t"                              \
        INSTRUCTION_MEASUREMENT_MARK_START                                     \
        INSTRUCTION_MEASUREMENT_MARK_END                                       \
        "sub %[ticks], %[totalTicks]        \n\t"                              \
        "decq %[counter]                    \n\t"                              \
        "jnz %=b"                                                              \
        : [totalTicks] "=rm" (totalTicks), [ticks] "=r" (ticks),               \
            [counter] "=rm" (counter),                                         \
            [mem1] "=m" (mem1), [mem2] "=m" (mem2)                             \
        : [addrMem1] "r" (&mem1), [addrMem2] "r" (&mem2)                       \
        : "rax", "rdx" CLOBBER);                                               \
    return static_cast<float>(totalTicks) /                                    \
        INSTRUCTION_MEASUREMENT_NUM_RUN_REPS /                                 \
        INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS;                              \
}

#define INSTRUCTION_MEASUREMENT_DO(NAME)   \
    ::instmeas::funcs::internal::InstructionMeasurementFunc##NAME()

#define INSTRUCTION_MEASUREMENT_REG_CLOBBER(...) , __VA_ARGS__
