#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>

// Uncommment the following lines to change repetitions
// #define INSTRUCTION_MEASUREMENT_NUM_LISTING_REPS (1 << 12)
// #define INSTRUCTION_MEASUREMENT_NUM_RUN_REPS (1 << 12)

#include "libinstmeas.h"

#define COUT_MEASURE(X) std::cout << std::setw(12) << std::left << #X ":" \
    << std::setprecision(2) << std::fixed << std::setw(6) << std::right << X() \
    << "\n"

void DumpCPUInfo()
{
    std::fstream file("/proc/cpuinfo", std::fstream::in);
    std::ostringstream stream;
    while (file.good())
    {
        char buffer[256];
        file.read(buffer, sizeof(buffer));
        stream.write(buffer, sizeof(buffer));
    }
    
    auto str = stream.str();
    std::regex modelNameRegex(R"(model name\s*\:\s*(.*)\r?\n?)");
    auto matchBegin = std::sregex_iterator(
        str.cbegin(), str.cend(), modelNameRegex);
    
    auto cpuNum = 0;
    for (auto it = matchBegin; it != std::sregex_iterator(); ++it, ++cpuNum)
    {
        auto match = *it;
        if (match.size() > 0)
        {
            std::cout << "Processor #" << cpuNum << " model name: " 
                << match[1].str() << "\n";
        }
    }
}

int main()
{
    using namespace instmeas::funcs;
    
    DumpCPUInfo();

    std::cout << "Beginning measurement...\n\n";

    COUT_MEASURE(IDIV_R64);
    COUT_MEASURE(XOR_R64);
    COUT_MEASURE(XOR_I32_R64);
    COUT_MEASURE(MOV_R_I64);
    COUT_MEASURE(INC_R64);
    COUT_MEASURE(DEC_R64);
    COUT_MEASURE(INC_M64);
    COUT_MEASURE(DEC_M64);
    COUT_MEASURE(INC_M32);
    COUT_MEASURE(DEC_M32);
    COUT_MEASURE(FMUL_ST_ST);
    // COUT_MEASURE(FSQRT); // Beat the processor serialization then uncomment

    std::cout << "\nFinished measurement!" << std::endl;
    return 0;
}
