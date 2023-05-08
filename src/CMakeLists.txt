cmake_minimum_required(VERSION 3.10)
# Updated to 3.22 to match the cmake version on CSIF
# Defines the minimum required cmake version
# You can check cmake version on your os by typing 
# `cmake --version` on the terminal

project(hw0 VERSION 1.1.0)
# Project Name and Version

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
    CACHE STRING "Choose the type of build, options are: None Debug Release asan"
    FORCE)
    
# AddressSanitize
set(CMAKE_C_FLAGS_ASAN
    "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1 -Wall -Wextra -Wpedantic -Werror"
    CACHE STRING "Flags used by the C compiler during AddressSanitizer builds."
    FORCE)
set(CMAKE_CXX_FLAGS_ASAN
    "-fsanitize=address -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1 -Wall -Wextra -Wpedantic -Werror"
    CACHE STRING "Flags used by the C++ compiler during AddressSanitizer builds."
    FORCE)


include_directories(${INCLUDE_DIR})

set(SOURCE_FILES main.c)
add_executable(Main ${SOURCE_FILES})

add_library(QuickSort SHARED
    ${LIB_DIR}/quick_sort.c
)
add_library(GenericTraits SHARED
    ${LIB_DIR}/GenericTraits.c
    ${LIB_DIR}/Int.c
    ${LIB_DIR}/Human.c
    ${LIB_DIR}/Student.c
    ${LIB_DIR}/Rectangle.c
)

target_link_libraries(Main QuickSort GenericTraits)

set_property(TARGET Main GenericTraits QuickSort PROPERTY C_STANDARD 99)
