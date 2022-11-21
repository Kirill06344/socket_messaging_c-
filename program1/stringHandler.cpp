#include "stringHandler.h"
#include <iostream>

namespace {
  bool isValid(const std::string& tmp) {
    return tmp.length() <= 64 && std::all_of(tmp.begin(), tmp.end(), [] (char c){return std::isdigit(c);});
  }

  struct additionOnParity{
    std::string operator()(const std::string& l, char c) {
      if ((c - '0') % 2 == 0) return l + "KB";
      return l + c;
    }
  };

  int sum(int init, char c) {
    return std::isdigit(c) ? init + (c -'0') : init;
  }

  int sumOfDigits(const std::string& data) {
    int init = 0;
    return std::accumulate(data.begin(), data.end(), init, sum);
  }
}

bazhenov::StringHandler::StringHandler() : input(true)
{}

void bazhenov::StringHandler::startProcessing(std::istream& is)
{
  sender.connectToServer();
  std::string tmp;
  while(input && std::getline(is, tmp)) {
    if (tmp.empty()) {
      input = false;
    } else {
      if (isValid(tmp)) {
        modify(tmp);
        std::lock_guard< std::mutex > lk(mut);
        buffer.push_back(std::move(tmp));
      }
    }
    readyToSend.notify_one();
  }
}

void bazhenov::StringHandler::bufferProcessing() {
  while(input) {
    std::unique_lock< std::mutex > lk(mut);
    readyToSend.wait(lk, [=] {return !buffer.empty() || !input;});
    if (!buffer.empty()) {
      std::string data = buffer.front();
      buffer.pop_front();
      lk.unlock();
      std::cout << data << std::endl;
      sender.sendMessage(std::to_string(sumOfDigits(data)));
    }
  }
}

void bazhenov::StringHandler::modify(std::string& tmp)
{
  std::sort(tmp.begin(), tmp.end(), std::greater<>());
  std::string res;
  tmp = std::accumulate(tmp.begin(), tmp.end(), res, additionOnParity());;
}
