#include <iostream>
#include "threadGuard.h"
#include "stringHandler.h"

int main()
{
  bazhenov::StringHandler sh;
  std::thread buffProcess(&bazhenov::StringHandler::bufferProcessing, std::ref(sh));
  bazhenov::ThreadGuard guard(buffProcess);
  sh.startProcessing(std::cin);
}
