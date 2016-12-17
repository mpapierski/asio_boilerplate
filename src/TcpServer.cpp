#include "TcpServer.h"

TcpServer::TcpServer(boost::asio::io_service& io_service,
                     const boost::asio::ip::tcp::endpoint& endpoint)
    : acceptor_(io_service, endpoint) {}

void TcpServer::start_accept() {
  TcpConnection::pointer new_connection =
      TcpConnection::create(acceptor_.get_io_service());

  acceptor_.async_accept(
      new_connection->socket(),
      boost::bind(&TcpServer::handle_accept, this,
                  boost::asio::placeholders::error, new_connection));
}

void TcpServer::handle_accept(const boost::system::error_code& error,
                              TcpConnection::pointer new_connection) {
  if (!error) {
    new_connection->start();
  }

  start_accept();
}