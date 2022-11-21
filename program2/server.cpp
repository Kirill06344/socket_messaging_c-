#include "server.h"
#include <iostream>
#include <arpa/inet.h>
#include <stdexcept>

bazhenov::Server::Server() : newfd(-1)
{
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
}

void bazhenov::Server::init()
{
  int rv = 0;
  if ((rv = getaddrinfo(nullptr, "3490", &hints, &server)) == -1) {
    std::cerr << gai_strerror(rv) << std::endl;
    return;
  }

  addrinfo * p;
  for(p = server; p != nullptr; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
      continue;
    }
    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      continue;
    }
    break;
  }
  freeaddrinfo(server);

  if (p == nullptr) {
    std::cerr << "Failed to bind!" << std::endl;
    return;
  }

  if (listen(sockfd, 10) == -1) {
    std::cerr << "Server: unable to listen!" << std::endl;
    return;
  }

  std::cout << "Waiting for connections!" << std::endl;
}

void bazhenov::Server::acceptClient()
{
  socklen_t sinsize = sizeof(theirAddr);
  newfd = accept(sockfd, (sockaddr*)&theirAddr, &sinsize);
  if (newfd == -1) {
    std::cerr << "Client is not acceptable to connect!" << std::endl;
    throw std::logic_error("Client has to send one message - it is key to reconnect!");
  }
  getMessage();
}

void bazhenov::Server::getMessage()
{
  while(true) {
    int numbytes = 0;
    char buf[50];
    if ((numbytes = recv(newfd, buf, 50, 0)) == -1) {
      std::cerr << "Unable to read!" << std::endl;
      continue;
    } else if (numbytes == 0) {
      newfd = -1;
      break;
    }
    buf[numbytes] = '\0';
    std::cout << buf << std::endl;
  }
}

bazhenov::Server::~Server()
{
  close(sockfd);
  close(newfd);
}

void* bazhenov::Server::getAddr(sockaddr* sa)
{
  if (sa->sa_family == AF_INET) {
    return &(((sockaddr_in*)sa)->sin_addr);
  }
  return &(((sockaddr_in6*)sa)->sin6_addr);
}

void bazhenov::Server::whoIsYourClient()
{
  if (newfd != -1) {
    char s[INET6_ADDRSTRLEN];
    inet_ntop(theirAddr.ss_family, getAddr((sockaddr*) &theirAddr), s, sizeof(s));
    std::cout << "Server got connection with " << s << std::endl;
  } else {
    std::cout << "Client is absent!" << std::endl;
  }
}



