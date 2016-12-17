cmake_minimum_required (VERSION 3.0)
project (
    asio_boilerplate
    VERSION 0.0.1
    LANGUAGES CXX
    )

option (BUILD_TESTS "Build tests" OFF)

# Check for all possible non portable functions
include (CheckFunctionExists)
check_function_exists (fork HAVE_FORK)

configure_file (
    config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories (${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory (src)

if (BUILD_TESTS)
    enable_testing ()
    add_subdirectory (tests)
endif ()
