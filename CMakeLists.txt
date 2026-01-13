# Custom embedded build for Shardy, targgeting minimal build as a part of
# tt-mlir MLIR project. This CMakeLists.txt file is mainly from StableHLO.

cmake_minimum_required(VERSION 3.15.0)

# CMP0116: Ninja generators transform `DEPFILE`s from `add_custom_command()`
# New in CMake 3.20. https://cmake.org/cmake/help/latest/policy/CMP0116.html
if(POLICY CMP0116)
  cmake_policy(SET CMP0116 OLD)
endif()

option(SHARDY_EMBEDDED_BUILD "Build Shardy as part of another project" ON)
option(SHARDY_ENABLE_LLD "Use LLD as the linker if available" OFF)

message(STATUS "Building Shardy embedded in another project")
project(shardy LANGUAGES CXX C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

find_package(MLIR REQUIRED CONFIG)

set(LLVM_RUNTIME_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/bin)
set(LLVM_LIBRARY_OUTPUT_INTDIR ${CMAKE_BINARY_DIR}/lib)
list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
include(HandleLLVMOptions)

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(AddMLIRPython)

include(CheckCXXCompilerFlag)
include(CheckLinkerFlag)

if (SHARDY_ENABLE_LLD)
  message(STATUS "Enabling LLD as the linker")
  add_link_options("-fuse-ld=lld")
endif()

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
link_directories(${LLVM_BUILD_LIBRARY_DIR})
add_definitions(${LLVM_DEFINITIONS})

set(SHARDY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SHARDY_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

add_compile_options(-Wno-deprecated-declarations -Wno-unused-but-set-variable -Wno-sign-compare -Wno-defaulted-function-deleted)

add_subdirectory(shardy/common)
add_subdirectory(shardy/dialect/sdy/ir)
add_subdirectory(shardy/dialect/sdy/transforms)
add_subdirectory(shardy/dialect/mpmd/ir)
add_subdirectory(shardy/dialect/mpmd/transforms)
add_subdirectory(shardy/integrations/python/ir)
add_subdirectory(shardy/integrations/c)