# tests/CMakeLists.txt

# Set test project name variable
set(testProjectName ${projectName}_Tests)

# Collect all test source files using file(GLOB ...)
set(TEST_SOURCES
    test_main.cpp
)

include(GoogleTest)

# Loop over each test source file and create a separate test executable
# Create the test executable encompassing all test sources
add_executable(${testProjectName} ${TEST_SOURCES})

# Include directories for the test executable
target_include_directories(${testProjectName} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${googletest_SOURCE_DIR}/googletest/include
)

# Link the test executable against your project library and Google Test libraries
target_link_libraries(${testProjectName} PRIVATE
    ${projectName}_lib
    GTest::gtest
    GTest::gtest_main
)

# Automatically discover and register tests
gtest_discover_tests(${testProjectName})
