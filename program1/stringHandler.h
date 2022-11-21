#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H
#include "sender.h"

namespace bazhenov {
  class StringHandler {
    public:
    StringHandler();
    void startProcessing(std::istream& is);
    void bufferProcessing();

    private:
    std::mutex mut;
    std::condition_variable readyToSend;
    std::deque< std::string > buffer;
    Sender sender;
    bool input;
    void modify(std::string& tmp);
  };
}


#endif
