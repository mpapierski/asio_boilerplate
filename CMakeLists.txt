cmake_minimum_required (VERSION 2.6)
project (asio_boilerplate CXX)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 0)
set (VERSION_PATCH 1)

option (BUILD_TESTS "Build tests" OFF)

configure_file (
	config.h.in
	${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories (${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory (src)

if (BUILD_TESTS)
	enable_testing ()
	add_subdirectory (tests)
endif ()
