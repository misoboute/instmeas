# instmeas (CPU Instruction Measurement)
This is a library of individual functions each of which measures the runtime of 
a single CPU instruction with particular operands. The runtimes are expressed
in CPU clock ticks.

## Usage
This tool can be used to measure the performance of the architecture of a 
CPU independent of its clock rate. 

This code has been tested on Windows and Linux using LLVM clang. g++ might 
also work. MSVC is not supported. Processors older than Intel Pentium are not
supported.

## Sample output
This is the output of the code run on the processor 
_Intel(R) Xeon(R) W-2135 CPU @ 3.70GHz_:

```
Beginning measurement...

IDIV_R64: 19.8942
XOR_R_R64: 0.275042
MOV_R_I64: 0.381724

Finished measurement!
```

This is the output of the code run on an unknown processor on 
[onlinegdb](https://onlinegdb.com/Sg_CnU8eWQ):

```
Beginning measurement...

IDIV_R64: 21.5383
XOR_R_R64: 0.298239
MOV_R_I64: 0.422997

Finished measurement!
```

This is the output of the code run on an unknown processor on 
[godbolt](https://godbolt.org/):

```
Beginning measurement...

IDIV_R64: 22.4963
XOR_R_R64: 0.321119
MOV_R_I64: 0.373963

Finished measurement!
```

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
listing 1024 times, surrounds the repeated listing by two CPU time 
measurements (using `RDTSC`), and calculates the CPU time difference. Then, 
whole cycle of measuring CPU time for the repeated listing is run 1024 times
adding the runtime of each cycle to a sum. This means that the original 
listing is run 1024 * 1024 times. The final sum is divided by this number to 
yield a floating point value denoting the average number of CPU cycles that
the listing takes.

When adding new measurement definitions using the 
`INSTRUCTION_MEASUREMENT_DEFINE` macro, three arguments are needed. The first 
argument is the measurement name. This can be any valid C identifier. 
The second one is the assembly listing to be measured. The listings should be
in the ATT dialect of assembly which used by `gas` by default. 
The third argument should be left empty unless the listing modifies any 
registers other than `RAX` and `RDX`. In such cases, the third argument 
should be an invocation of the `INSTRUCTION_MEASUREMENT_REG_CLOBBER` 
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
