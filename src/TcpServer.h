#if !defined(TCP_SERVER_HPP_INCLUDED_)
#define TCP_SERVER_HPP_INCLUDED_

#include <boost/asio.hpp>
#include "tcp_connection.hpp"

/**
 * This is the TCP server code
 */
class tcp_server {
 public:
  tcp_server(boost::asio::io_service& io_service,
             const boost::asio::ip::tcp::endpoint& endpoint);
  /**
   * Starts new asynchronous accept
   */
  void start_accept();
  /**
   * New client is connected
   */
  void handle_accept(const boost::system::error_code& error,
                     tcp_connection::pointer new_connection);

 private:
  boost::asio::ip::tcp::acceptor acceptor_;
};

#endif