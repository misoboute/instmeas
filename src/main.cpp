#include <iostream>

#include "libinstmeas.h"

int main()
{
    using namespace instmeas::funcs;
    std::cout << "Beginning measurement...\n\n";
    std::cout << "IDIV_R64: " << IDIV_R64() << "\n";
    std::cout << "XOR_R_R64: " << XOR_R_R64() << "\n";
    std::cout << "MOV_R_I64: " << MOV_R_I64() << "\n";
    std::cout << "\nFinished measurement!" << std::endl;
    return 0;
}
