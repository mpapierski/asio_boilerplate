#if !defined(ECHOPROTOCOL_H_INCLUDED_)
#define ECHOPROTOCOL_H_INCLUDED_

#include "Protocol.h"

class EchoProtocol : public Protocol {
 public:
  void onIngress(const boost::asio::const_buffer& data) override;
  void onEgress(const boost::asio::const_buffer& data) override;
};

#endif