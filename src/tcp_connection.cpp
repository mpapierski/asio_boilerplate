#include "tcp_connection.hpp"

tcp_connection::tcp_connection(boost::asio::io_service & io_service)
	: socket_(io_service)
{
}

void tcp_connection::start()
{
}
