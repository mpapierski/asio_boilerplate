#include "TcpConnection.h"

TcpConnection::TcpConnection(boost::asio::io_service& io_service)
    : socket_(io_service) {}

void TcpConnection::start() {
  // Start asynchronous read
  socket_.async_read_some(
      boost::asio::buffer(data_),
      boost::bind(&TcpConnection::handle_read, shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::handle_read(const boost::system::error_code& error,
                                std::size_t bytes_transferred) {
  if (error) {
    return;
  }
  // Start asynchronous write
  boost::asio::async_write(
      socket_, boost::asio::buffer(data_, bytes_transferred),
      boost::bind(&TcpConnection::handle_write, shared_from_this(),
                  boost::asio::placeholders::error));
}

void TcpConnection::handle_write(const boost::system::error_code& error) {
  if (error) {
    return;
  }
  start();
}