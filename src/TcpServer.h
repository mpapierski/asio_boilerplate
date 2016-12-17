#if !defined(TCP_SERVER_H_INCLUDED_)
#define TCP_SERVER_H_INCLUDED_

#include <boost/asio.hpp>
#include "TcpConnection.h"

/**
 * This is the TCP server code
 */
class TcpServer {
 public:
  TcpServer(boost::asio::io_service& io_service,
            const boost::asio::ip::tcp::endpoint& endpoint);
  /**
   * Starts new asynchronous accept
   */
  void start();

 private:
  boost::asio::ip::tcp::acceptor acceptor_;
  /**
   * New client is connected
   */
  void handleAccept(const boost::system::error_code& error,
                    TcpConnection::pointer newConnection);
};

#endif