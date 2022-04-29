#include <iomanip>
#include <iostream>

#include "libinstmeas.h"

#define COUT_MEASURE(X) std::cout << std::setw(12) << std::left << #X ":" \
    << std::setprecision(2) << std::fixed << std::setw(6) << std::right << X() << "\n"

int main()
{
    using namespace instmeas::funcs;
    std::cout << "Beginning measurement...\n\n";

    COUT_MEASURE(IDIV_R64);
    COUT_MEASURE(XOR_R_R64);
    COUT_MEASURE(MOV_R_I64);
    COUT_MEASURE(INC_R64);
    COUT_MEASURE(DEC_R64);
    COUT_MEASURE(INC_M64);
    COUT_MEASURE(DEC_M64);
    COUT_MEASURE(INC_M32);
    COUT_MEASURE(DEC_M32);

    std::cout << "\nFinished measurement!" << std::endl;
    return 0;
}
