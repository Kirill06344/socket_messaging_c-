#ifndef THREADGUARD_H
#define THREADGUARD_H

#include <thread>

namespace bazhenov {
  class ThreadGuard {
    public:
    explicit ThreadGuard(std::thread& t);
    ~ThreadGuard();
    private:
    std::thread& t_;
  };
}


#endif
