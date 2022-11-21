#include "sender.h"
#include <iostream>

Sender::Sender() {
  memset(&hints,0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
}

void Sender::connectToServer()
{
  int rv = 0;
  if ((rv = getaddrinfo("127.0.0.1", "3490", &hints, &server)) != 0) {
    std::cerr << "Unable to connect to server, the program will not be able to communicate with server!" << std::endl;
  } else {
    for (p = server; p != nullptr; p = p->ai_next) {
      if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
        continue;
      }
      if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
        close(sockfd);
        continue;
      }
      break;
    }
    if (p == nullptr) {
      std::cerr << "Failed to connect with sever!" << std::endl;
    } else {
      std::cout << "Successful connection with server!" << std::endl;
    }
  }
  freeaddrinfo(server);
}

void Sender::sendMessage(const std::string& msg)
{
  const char * cMsg = msg.c_str();
  if (send(sockfd, cMsg, strlen(cMsg) + 1, MSG_NOSIGNAL) == -1) {
    connectToServer();
    send(sockfd, cMsg, strlen(cMsg) + 1, MSG_NOSIGNAL);
  }
}

Sender::~Sender()
{
  close(sockfd);
}


