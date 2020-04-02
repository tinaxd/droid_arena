cmake_minimum_required (VERSION 3.10)
project (droidarena CXX)

set (CMAKE_CXX_STANDARD 17)

# https://medium.com/@alasher/colored-c-compiler-output-with-ninja-clang-gcc-10bfe7f2b949
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
endif ()

set (CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*,performance-*,clang-analyzer-*,boost-* -fix -fix-errors)

add_subdirectory (src)
