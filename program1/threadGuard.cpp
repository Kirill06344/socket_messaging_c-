#include "threadGuard.h"

bazhenov::ThreadGuard::ThreadGuard(std::thread& t) : t_(t){}

bazhenov::ThreadGuard::~ThreadGuard()
{
  if (t_.joinable()) {
    t_.join();
  }
}

