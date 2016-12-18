#if !defined(CLIENT_H_INCLUDED_)
#define CLIENT_H_INCLUDED_

#include "Callback.h"

class Client : public Callback {
 public:
  void onError(const boost::system::error_code& error) override;
};

#endif
