cmake_minimum_required(VERSION 3.30.3)
enable_testing()
# Set project name variable
set(projectName GameOfLife_raylib)

# Set project name
project(${projectName} LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.15.2
)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 5.0
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(raylib)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)