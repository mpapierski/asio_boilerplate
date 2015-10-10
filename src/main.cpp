#include <iostream>
#include <boost/asio.hpp>
#include "tcp_server.hpp"

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " [port]" << std::endl;
		return 1;
	}
	boost::asio::io_service io_service;
	// Prepare server
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), std::atoi(argv[1]));
	tcp_server server(io_service, endpoint);
	server.start_accept();
	io_service.run();
}