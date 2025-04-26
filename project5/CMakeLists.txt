cmake_minimum_required(VERSION 3.13.4)
project(ProgramAnalysis)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(ProgramAnalysis MODULE DeadCodeDetector.cpp)

set_target_properties(ProgramAnalysis PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  PREFIX "")
