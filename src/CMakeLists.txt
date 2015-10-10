find_package (Boost REQUIRED COMPONENTS
	system
	program_options)

include_directories (${Boost_INCLUDE_DIRS})

add_executable (asio_boilerplate
	main.cpp
	tcp_connection.cpp
	tcp_server.cpp)
target_link_libraries (asio_boilerplate
	${Boost_LIBRARIES})
