#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <iosfwd>

#ifndef SERVER_H
#define SERVER_H
namespace bazhenov {
  class Server {
    public:
      Server();
      void init();
      void acceptClient();
      void whoIsYourClient();
      ~Server();
    private:
      int sockfd, newfd;
      addrinfo hints, * server;
      sockaddr_storage theirAddr;
      void * getAddr(sockaddr* sa);
      void getMessage();
  };
}
#endif
