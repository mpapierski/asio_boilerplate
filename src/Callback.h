#if !defined(CALLBACK_H_INCLUDED_)
#define CALLBACK_H_INCLUDED_

#include <boost/asio.hpp>

class Callback {
 public:
  /**
   * Called when client error is encountered
   * @param
   */
  virtual void onError(const boost::system::error_code&) = 0;
};

#endif