#ifndef PROGRAM1_SENDER_H
#define PROGRAM1_SENDER_H
#include <iosfwd>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <algorithm>
#include <numeric>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

class Sender {
  public:
  Sender();
  void connectToServer();
  void sendMessage(const std::string & msg);
  ~Sender();
  private:
  int sockfd;
  addrinfo hints, *server;
  addrinfo * p;
};
#endif
