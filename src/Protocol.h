#if !defined(PROTOCOL_H_INCLUDED_)
#define PROTOCOL_H_INCLUDED_

#include <memory>
#include "Callback.h"

class Protocol {
 public:
  /**
   * Process incoming data and call some callbacks
   */
  virtual void onIngress(const boost::asio::const_buffer& data) = 0;
  /**
   * Process outgoing data
   */
  virtual void onEgress(const boost::asio::const_buffer& data) = 0;

 private:
  Callback* callbacks;
};

#endif