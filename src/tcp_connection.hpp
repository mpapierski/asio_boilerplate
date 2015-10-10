#if !defined(TCP_CONNECTION_HPP_INCLUDED_)
#define TCP_CONNECTION_HPP_INCLUDED_

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

/**
 * TCP connection class
 */
class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;
	inline static pointer create(boost::asio::io_service & io_service)
	{
		return pointer(new tcp_connection(io_service));
	}
	/**
	 * Starts reading on a socket
	 */
	void start();
	/**
	 * Returns the socket used for this connection
	 */
	inline boost::asio::ip::tcp::socket & socket()
	{
		return socket_;
	}
private:
	tcp_connection(boost::asio::io_service & io_service);
	boost::asio::ip::tcp::socket socket_;
};

#endif