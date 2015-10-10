#include <iostream>
#include <boost/asio.hpp>
#include "tcp_server.hpp"

int main(int argc, char * argv[])
{
	boost::asio::io_service io_service;
	tcp_server server(io_service);
	server.start_accept();
	io_service.run();
}