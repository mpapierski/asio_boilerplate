#include <iostream>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include "tcp_server.hpp"
#include "config.h"

int main(int argc, char * argv[])
{
	namespace po = boost::program_options;
	unsigned short port;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "show help message")
		("version", "show version")
		("port,p", po::value<unsigned short>(&port)->required(), "port")
	;
	po::variables_map vm;
	try
	{
		po::store(po::parse_command_line(argc, argv, desc), vm);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	if (vm.count("help"))
	{
		std::cout << desc << std::endl;
		return 0;
	}
	if (vm.count("version"))
	{
		std::cout << argv[0] << ' ' << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH << std::endl;
		return 0;
	}
	try
	{
		po::notify(vm);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	boost::asio::io_service io_service;
	// Prepare server
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	tcp_server server(io_service, endpoint);
	server.start_accept();
	io_service.run();
}