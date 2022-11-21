#include <iostream>
#include "server.h"

int main()
{
  bazhenov::Server server;
  server.init();
  try {
    while (true) {
      server.acceptClient();
    }
  } catch (const std::exception& ex) {
    std::cerr<< ex.what() << std::endl;
    return 1;
  }
}
