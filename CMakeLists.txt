cmake_minimum_required(VERSION 3.10)

project(Test) # Project name

# Get all source files
file(GLOB SOURCES "src/*.cpp")

# Find catalyst using catalyst-config.cmake
find_package(catalyst
             REQUIRED
             COMPONENTS SDK)

# Find catalyst using catalyst-config.cmake
find_package(MPI REQUIRED)

# Create executable
add_executable(Test ${SOURCES})
FIND_PATH(MPI_INTEL_CXX mpicxx $ENV{PATH})
message(MPI_INTEL_CXX)

set(CMAKE_CXX_COMPILER  "/usr/bin/mpicxx")
message(${MPI_CXX_COMPILE_FLAGS})
# target_compile_options(Test PRIVATE ${MPI_CXX_COMPILE_FLAGS})

# Include libraries
include_directories(include)


include_directories(${MPI_INCLUDE_PATH})


# link catalyst
target_link_libraries(Test PRIVATE catalyst::catalyst)

# link catalyst
target_link_libraries(Test PRIVATE catalyst::conduit)

