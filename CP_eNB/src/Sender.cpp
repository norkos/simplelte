#include <memory>
#include <MessageBase.hpp>
#include <Logger.hpp>

#include "Sender.hpp"

namespace lte 
{
namespace enb
{

namespace 
{
decltype(auto) serialize(const util::Message& msg)
{
    std::string message;
    msg.SerializeToString(&message);

    auto result = std::make_unique<zmq::message_t>(message.size());
    memcpy((void*)result->data(),  message.c_str(), message.size());
    
    return result; 
}
}
void Sender::send(std::unique_ptr<util::Message> msg)
{
  //dbg() << "Sending: " << *msg;
  auto response = serialize(*msg);
  socket_.send (*response);
}

}
}
