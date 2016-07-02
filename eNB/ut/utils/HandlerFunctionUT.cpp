#include <gtest/gtest.h>
#include <memory>

#include "utils/HandlerFunction.hpp"
#include "Message.hpp"


namespace GT = ::testing;

namespace ut
{

struct Message {
};
    
struct FirstMessage :  Message{
};

struct SecondMessage : Message{
};

enum Status { none, first, second };
  
struct Runner {
    Status status = Status::none;
    
    void first(const FirstMessage&) { status = Status::first;}
    void second(const SecondMessage&) { status =  Status::second; }
};

TEST(handler_function, execute_first)
{
    Runner runner;
    std::shared_ptr<Message> msg = std::make_shared<FirstMessage>();
    std::shared_ptr<HandlerFunctionBase<Message>> handler = std::make_shared<HandlerFunction<Runner, FirstMessage, Message>>(&runner, &Runner::first);
    handler->execute(*msg);
    ASSERT_EQ(runner.status, Status::first);
}

TEST(handler_function, execute_second)
{
    Runner runner;
    std::shared_ptr<Message> msg = std::make_shared<SecondMessage>();
    std::shared_ptr<HandlerFunctionBase<Message>> handler = std::make_shared<HandlerFunction<Runner, SecondMessage, Message>>(&runner, &Runner::second);
    handler->execute(*msg);
    ASSERT_EQ(runner.status, Status::second);
}

}