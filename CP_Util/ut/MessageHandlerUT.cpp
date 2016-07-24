#include <gtest/gtest.h>
#include <memory>

#include "MessageHandler.hpp"

namespace GT = ::testing;

namespace lte
{
namespace util
{
namespace ut
{
    
struct Message {
    virtual ~Message(){} // we need polymorphism
};
    
struct FirstMessage : Message{
};

struct SecondMessage : Message{
};

enum Status { none, first, second };
  
struct Runner {
    Status status = Status::none;
    
    void on_first_message(const FirstMessage&) { status = Status::first;}
    void on_second_message(const SecondMessage&) { status =  Status::second;}
};

class MessageHandlerTest : public ::testing::Test{
public:
    Runner runner_;
    
    void SetUp(){
        runner_.status = Status::none;
    }
};

TEST_F(MessageHandlerTest, message_was_not_handled)
{
    const Message& msg = FirstMessage();
    MessageHandler<Message> sut;
    
    auto message_was_handled = sut.handleMessage(msg);
    
    ASSERT_FALSE(message_was_handled);
}

TEST_F(MessageHandlerTest, execute_first)
{
    const Message& msg = FirstMessage();
    MessageHandler<Message> sut;
    
    sut.registerMessage(runner_, &Runner::on_first_message);
    auto message_was_handled = sut.handleMessage(msg);
    
    ASSERT_TRUE(message_was_handled);
    ASSERT_EQ(runner_.status, Status::first);
}

TEST_F(MessageHandlerTest, execute_second)
{
    const Message& msg = SecondMessage();
    MessageHandler<Message> sut;
    
    sut.registerMessage(runner_, &Runner::on_first_message);
    sut.registerMessage(runner_, &Runner::on_second_message);
    sut.handleMessage(msg);
    
    ASSERT_EQ(runner_.status, Status::second);
}
}
}
}