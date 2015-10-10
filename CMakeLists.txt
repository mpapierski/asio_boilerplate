cmake_minimum_required (VERSION 2.6)
project (asio_boilerplate CXX)

option (BUILD_TESTS "Build tests" OFF)

add_subdirectory (src)

if (BUILD_TESTS)
	enable_testing ()
	add_subdirectory (tests)
endif ()
