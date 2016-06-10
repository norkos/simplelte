#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <google/protobuf/message.h>

typedef google::protobuf::Message Message;

class MessageHandler{
public:
    void handleMessage(const Message*);
    ~MessageHandler(){}
};

#endif