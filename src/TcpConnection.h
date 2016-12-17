#if !defined(TCP_CONNECTION_H_INCLUDED_)
#define TCP_CONNECTION_H_INCLUDED_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

/**
 * TCP connection class
 */
class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
 public:
  typedef boost::shared_ptr<TcpConnection> pointer;
  inline static pointer create(boost::asio::io_service& io_service) {
    return pointer(new TcpConnection(io_service));
  }
  /**
   * Starts reading on a socket
   */
  void start();
  /**
   * Returns the socket used for this connection
   */
  inline boost::asio::ip::tcp::socket& socket() { return socket_; }

 private:
  TcpConnection(boost::asio::io_service& io_service);
  /**
   * Received data from client
   */
  void handle_read(const boost::system::error_code& error,
                   std::size_t bytes_transferred);
  /**
   * Data is delivered to client
   */
  void handle_write(const boost::system::error_code& error);
  boost::asio::ip::tcp::socket socket_;
  enum { max_size = 1024 };
  boost::array<char, max_size> data_;
};

#endif