find_package (Boost REQUIRED COMPONENTS
    system
    program_options
    )

include_directories (
    ${Boost_INCLUDE_DIRS}
    )

add_executable (asio_boilerplate
    main.cpp
    TcpConnection.cpp
    TcpServer.cpp
    )
target_link_libraries (asio_boilerplate
    ${Boost_LIBRARIES}
    )
