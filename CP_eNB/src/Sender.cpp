#include <memory>
#include <messages.pb.h>
#include <MessageBase.hpp>
#include "Sender.hpp"

namespace lte 
{
namespace enb
{

std::unique_ptr<zmq::message_t> serialize(const lte::util::Message& msg)
{
    std::string message;
    msg.SerializeToString(&message);

    auto result = std::make_unique<zmq::message_t>(message.size());
    memcpy((void*)result->data(),  message.c_str(), message.size());
    
    return result; 
}

void Sender::send(std::unique_ptr<lte::util::Message> msg)
{
  auto response = serialize(*msg);
  socket_.send (*response);
}

}
}
