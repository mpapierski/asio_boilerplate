#include "tcp_server.hpp"

static boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 1234);

tcp_server::tcp_server(boost::asio::io_service & io_service)
	: acceptor_(io_service, endpoint)
{
}

void tcp_server::start_accept()
{
	tcp_connection::pointer new_connection =
		tcp_connection::create(acceptor_.get_io_service());

	acceptor_.async_accept(new_connection->socket(),
		boost::bind(&tcp_server::handle_accept, this,
			boost::asio::placeholders::error,
			new_connection));
}

void tcp_server::handle_accept(const boost::system::error_code & error,
	tcp_connection::pointer new_connection)
{
	if (!error)
	{
		new_connection->start();
	}

	start_accept();
}