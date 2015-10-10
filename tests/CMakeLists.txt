find_package (PythonInterp)

if (PYTHONINTERP_FOUND)
	add_test (NAME integration_tests
		COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/integration_tests.py
			$<TARGET_FILE:asio_boilerplate>)
endif ()