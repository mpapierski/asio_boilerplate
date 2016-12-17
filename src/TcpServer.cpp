#include "TcpServer.h"

TcpServer::TcpServer(boost::asio::io_service& io_service,
                     const boost::asio::ip::tcp::endpoint& endpoint)
    : acceptor_(io_service, endpoint) {}

void TcpServer::start() {
  TcpConnection::pointer newConnection =
      TcpConnection::create(acceptor_.get_io_service());

  acceptor_.async_accept(
      newConnection->socket(),
      boost::bind(&TcpServer::handleAccept, this,
                  boost::asio::placeholders::error, newConnection));
}

void TcpServer::handleAccept(const boost::system::error_code& error,
                             TcpConnection::pointer newConnection) {
  if (!error) {
    newConnection->start();
  }
  start();
}