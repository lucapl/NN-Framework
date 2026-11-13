
cmake_minimum_required(VERSION 3.16)

project(Tensor
    VERSION 1.0.0
    LANGUAGES CXX
)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build the tensor library
add_library(tensor SHARED
    cpp/core/tensor/tensor.cpp
    cpp/core/tensor/tensor_operations.cpp
)

# Public include directories
target_include_directories(tensor
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/include
)

# Compiler warnings
target_compile_options(tensor
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# Position-independent code (useful for shared libraries)
set_target_properties(tensor PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

