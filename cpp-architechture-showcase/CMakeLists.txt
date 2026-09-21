cmake_minimum_required(VERSION 3.20)
project(CppArchitectureShowcase LANGUAGES CXX)

# Enforce Modern C++ (C++20 or C++23)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure compiler flags across environments
if(MSVC)
    add_compile_options(/W4 /WX) # High warning level, treat warnings as errors
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

# Include directories
include_directories(include)

# Find all your C++ source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "main.cpp")

# Define the final executable
add_executable(${PROJECT_NAME} ${SOURCES})
