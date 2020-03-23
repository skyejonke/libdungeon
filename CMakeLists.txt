# Basic setup
cmake_minimum_required(VERSION 3.5)
project (libdungeon LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Directories with header files
include_directories ("include")

# Setting compile flags
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add packages
# find_package(Boost REQUIRED COMPONENTS
#   random
  # )

# Libraries
add_library(libdungeon STATIC src/character.cpp)

target_link_libraries(libdungeon ${CONAN_LIBS})

# # Testing
# target_link_libraries(tests libdungeon)

# enable_testing()
# add_test(NAME mainTest COMMAND tests)
