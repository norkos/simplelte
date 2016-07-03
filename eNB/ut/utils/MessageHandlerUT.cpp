#include <gtest/gtest.h>
#include <memory>

#include "utils/MessageHandler.hpp"

namespace GT = ::testing;

namespace ut
{

struct Message {
    virtual ~Message(){} // we need polymorphism
};
    
struct FirstMessage :  Message{
};

struct SecondMessage : Message{
};

enum Status { none, first, second };
  
struct Runner {
    Status status = Status::none;
    
    void onFirstMessage(const FirstMessage&) { status = Status::first;}
    void onSecondMessage(const SecondMessage&) { status =  Status::second; }
};


TEST(MessageHandlerTest, message_was_not_handled)
{
    Runner  runner;
    const Message& msg = FirstMessage();
    
    MessageHandler<Message> handler;
    bool message_was_handled = handler.handleMessage(msg);
    
    ASSERT_FALSE(message_was_handled);
}

TEST(MessageHandlerTest, message_was_handled)
{
    Runner  runner;
    const Message& msg = FirstMessage();
    
    MessageHandler<Message> handler;
    handler.registerMessage(&runner, &Runner::onFirstMessage);
    bool message_was_handled = handler.handleMessage(msg);
    
    ASSERT_TRUE(message_was_handled);
}

TEST(MessageHandlerTest, execute_first)
{
    Runner  runner;
    const Message& msg = FirstMessage();
    
    MessageHandler<Message> handler;
    handler.registerMessage(&runner, &Runner::onFirstMessage);
    handler.handleMessage(msg);
    
    ASSERT_EQ(runner.status, Status::first);
}

TEST(MessageHandlerTest, execute_second)
{
    Runner  runner;
    const Message& msg = SecondMessage();
    
    MessageHandler<Message> handler;
    handler.registerMessage(&runner, &Runner::onSecondMessage);
    handler.handleMessage(msg);
    
    ASSERT_EQ(runner.status, Status::second);
}
}