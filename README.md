# instmeas (CPU Instruction Measurement)
This is a library of individual functions each of which measures the runtime of 
a single CPU instruction with particular operands. The runtimes are expressed
in CPU clock ticks.

## Usage
This tool can be used to measure the performance of the architecture of a 
CPU independent of its clock rate. 

This code has been tested on Windows and Linux using LLVM clang. g++ might 
also work. MSVC is not supported. An x86-64 processor is required.

## Sample output
### Sample 1
This is the output of the code run on the processor 
_Intel(R) Xeon(R) W-2135 CPU @ 3.70GHz_, Windows 10, clang 12

```
IDIV_R64:    34.97
XOR_R64:      0.27
XOR_I32_R64:  0.88
MOV_R_I64:    0.54
INC_R64:      0.90
DEC_R64:      0.85
INC_M64:      4.58
DEC_M64:      4.62
INC_M32:      4.64
DEC_M32:      4.63

Finished measurement!
```
_Note_: CPU info dump doesn't work for Windows!

### Sample 2
On Ubuntu 22.10, clang 13
```
Processor #0 model name: Intel(R) Core(TM) i7-4870HQ CPU @ 2.50GHz
Processor #1 model name: Intel(R) Core(TM) i7-4870HQ CPU @ 2.50GHz
Processor #2 model name: Intel(R) Core(TM) i7-4870HQ CPU @ 2.50GHz
Processor #3 model name: Intel(R) Core(TM) i7-4870HQ CPU @ 2.50GHz
Processor #4 model name: Intel(R) Core(TM) i7-4870HQ CPU @ 2.50GHz
Processor #5 model name: Intel(R) Core(TM) i7-4870HQ CPU @ 2.50GHz
Processor #6 model name: Intel(R) Core(TM) i7-4870HQ CPU @ 2.50GHz
Processor #7 model name: Intel(R) Core(TM) i7-4870HQ CPU @ 2.50GHz
Beginning measurement...

IDIV_R64:    16.12
XOR_R_R64:    0.34
MOV_R_I64:    0.56
INC_R64:      0.73
DEC_R64:      0.74
INC_M64:      4.50
DEC_M64:      4.49
INC_M32:      4.53
DEC_M32:      4.46

Finished measurement!
```

### Sample 3
On [onlinegdb](https://onlinegdb.com/ciK8AxYRZ):

```
Processor #0 model name: Intel(R) Xeon(R) CPU @ 2.00GHz
Processor #1 model name: Intel(R) Xeon(R) CPU @ 2.00GHz
Processor #2 model name: Intel(R) Xeon(R) CPU @ 2.00GHz
Processor #3 model name: Intel(R) Xeon(R) CPU @ 2.00GHz
Processor #4 model name: Intel(R) Xeon(R) CPU @ 2.00GHz
Processor #5 model name: Intel(R) Xeon(R) CPU @ 2.00GHz
Processor #6 model name: Intel(R) Xeon(R) CPU @ 2.00GHz
Processor #7 model name: Intel(R) Xeon(R) CPU @ 2.00GHz
Beginning measurement...

IDIV_R64:    30.64
XOR_R64:      0.23
XOR_I32_R64:  0.75
MOV_R_I64:    0.47
INC_R64:      0.75
DEC_R64:      0.75
INC_M64:      4.09
DEC_M64:      4.09
INC_M32:      4.10
DEC_M32:      4.10

Finished measurement!
```

### Sample 4
On [godbolt](https://godbolt.org/):

```
Processor #0 model name: AMD EPYC 7R32
Processor #1 model name: AMD EPYC 7R32
Beginning measurement...

IDIV_R64:    18.54
XOR_R64:      0.35
XOR_I32_R64:  0.94
MOV_R_I64:    0.87
INC_R64:      0.86
DEC_R64:      0.87
INC_M64:      6.02
DEC_M64:      5.99
INC_M32:      6.10
DEC_M32:      6.07

Finished measurement!
```

### Sample 5
On [godbolt](https://godbolt.org/):

```
Processor #0 model name: Intel(R) Xeon(R) Platinum 8275CL CPU @ 3.00GHz
Processor #1 model name: Intel(R) Xeon(R) Platinum 8275CL CPU @ 3.00GHz
Beginning measurement...

IDIV_R64:    35.41
XOR_R64:      0.35
XOR_I32_R64:  0.87
MOV_R_I64:    0.65
INC_R64:      0.86
DEC_R64:      0.87
INC_M64:      4.83
DEC_M64:      4.81
INC_M32:      4.66
DEC_M32:      4.63

Finished measurement!
```

### Sample 6
On [godbolt](https://godbolt.org/):

```
Processor #0 model name: Intel(R) Xeon(R) Platinum 8124M CPU @ 3.00GHz
Processor #1 model name: Intel(R) Xeon(R) Platinum 8124M CPU @ 3.00GHz
Beginning measurement...

IDIV_R64:    38.06
XOR_R64:      0.37
XOR_I32_R64:  0.91
MOV_R_I64:    0.91
INC_R64:      0.90
DEC_R64:      0.89
INC_M64:      4.75
DEC_M64:      4.74
INC_M32:      4.82
DEC_M32:      4.74

Finished measurement!
```

### Sample 7
On [godbolt](https://godbolt.org/):

```
Processor #0 model name: Intel(R) Xeon(R) Platinum 8375C CPU @ 2.90GHz
Processor #1 model name: Intel(R) Xeon(R) Platinum 8375C CPU @ 2.90GHz
Beginning measurement...

IDIV_R64:    11.63
XOR_R64:      0.26
XOR_I32_R64:  0.85
MOV_R_I64:    0.53
INC_R64:      0.85
DEC_R64:      0.89
INC_M64:      6.34
DEC_M64:      6.36
INC_M32:      6.34
DEC_M32:      6.30

Finished measurement!
```

It might not be easy to interpret these results. One could infer that,
more CPU cores allow the CPU to interleave execution of instructions that don't
depend on one another and perform them faster. This can be seen from smaller
measurement results for CPUs with 8-12 cores than those with only two. This 
effect might be countered by designing the measurement listing such that every
instruction depends on the result of the last one. This way, the processor
will have less opportunity for interleaving independent instructions and 
the instructions will more likely be executed sequentially.

## Details
The functions that measure the runtime of a single CPU instruction are declared 
in the namespace `instmeas::func` and are brought in by including 
`libinstmeas.h`.

A few examples of these functions and the singular CPU instruction that they 
measure:
- `IDIV_R64`: IDIV with a 64 bit register operand
- `XOR_R_R64`: IDIV with two 64 bit register operands
- `MOV_R_I64`: MOV with a 64 bit register and an immediate operand

Each of these functions uses an arithmatic expression made up of 
`INSTRUCTION_MEASUREMENT_DO` elements. The `INSTRUCTION_MEASUREMENT_DO` macro
invokes functions defined in the namespace `instmeas::func::internal` using 
the macro `INSTRUCTION_MEASUREMENT_DEFINE`.

As an example, to be able to measure the runtime of an IDIV instruction with a 
64 bit register operand, we inevitably have to precede the `IDIV` instruction 
with initializations of the registers `RAX`, `RBX`, and `RDX`. So, in the 
`internal` namespace, we define the measurement `MOV2_I_R64_XOR_R_R64_IDIV64` 
to measure the runtime of this listing:

```asm
    mov $39916801,%rax
    mov $5039,%rbx
    xor %rdx,%rdx
    idiv %rbx
```

But this adds the runtime of two `MOV`s and an `XOR` to the measurement. 
To compensate for this, we define another measurement `MOV2_I_R64_XOR_R_R64` 
to measure the runtime of the initialization part:

```asm
    mov $39916801,%rax
    mov $5039,%rbx
    xor %rdx,%rdx
```

Then, we could assume the runtime of a single `IDIV` instruction to be roughly 
equal to the differece of the two measurements. The function 
`instmeas::func::IDIV_R64` simply calculates and returns this difference.

## More Details
Each measurement definition takes an assembly listing as input, repeats the
listing _2 ^ 14_ times, surrounds the repeated listing by two CPU time 
measurements (using `RDTSC`), and calculates the CPU time difference. 
Then, the whole cycle of measuring CPU time for the 
repeated listing is executed _2 ^ 14_ times adding the runtime of each cycle 
to a sum.

During each cycle, an empty set of timing fences is added and measured to be
subtracted from the sum as the timing overhead. That is, in 
each cycle, apart from the actual measurement operation (mark start time, run
the repeated listing, mark end time), we also execute all the 
instructions that are required for the measurement only. We take this to be
the measurement overhead in each cycle. Therefore, during each cycle we
subtract the overhead measurement from the total sum.

This means that when the loop is finished running, the original 
listing has run 2 ^ 28 times. The final sum is divided by this number to 
yield a floating point value denoting the average number of CPU cycles that
the listing takes.

To disable the repetition of the listing before inserting it between the timing
fences or change the number of times you want the listing to be repeated,
define the macro `INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS` and set it to `1`
(to disable the repetition) or another power of power of 2 (up to and including 
2 ^ 20) before including the header. Take care if you change this value. 
Higher values for this number make both the compile time and the runtime 
exponentially longer!

Likewise, to change the number of times to run the measurement
cycle, define the macro `INSTRUCTION_MEASUREMENT_NUM_RUN_REPS` to the desired
value before including the header. This number is also recommended to be 
a power of two. Higher values for this macro could lead to exponentially 
longer runtimes.

When adding new measurement definitions using the 
`INSTRUCTION_MEASUREMENT_DEFINE` macro, three arguments are needed. The first 
argument is the measurement name. This can be any valid C identifier. 
The second one is the assembly listing to be measured. The listings should be
in the ATT dialect of assembly which used by `gas` by default. 
The third argument should be left empty unless the listing modifies any 
registers other than `RAX` and `RDX`. In such cases, the third 
argument should be an invocation of the `INSTRUCTION_MEASUREMENT_REG_CLOBBER` 
macro. For example, since the measurement `MOV2_I_R64_XOR_R_R64_IDIV64` in the
examples above uses and modifies the registers `RAX`, `RBX`, and `RDX`, it 
will look like this:
```C++
INSTRUCTION_MEASUREMENT_DEFINE(MOV2_I_R64_XOR_R_R64_IDIV64, 
    "mov $39916801,%%rax\n\tmov $5039,%%rbx\n\txor %%rdx,%%rdx\n\tidiv %%rbx",
    INSTRUCTION_MEASUREMENT_REG_CLOBBER("rbx"))
```

## Contribution
You can send me an email if you have something to add/improve and I'll be happy 
to add you as a contributor or just incorporate fresh ideas into the code.
One thing is certain: there are a lot of other instructions that need to be 
added.
