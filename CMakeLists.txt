# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (CPUInstructionMeasurement)

set(INSTMEAS_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Add source to this project's executable.
add_executable (CPUInstructionMeasurement
    src/main.cpp
)

target_include_directories(
    CPUInstructionMeasurement PRIVATE ${INSTMEAS_ROOT}/include)
