#include "ZMQClient.hpp"
#include "Deserializer.hpp"
#include <Logger.hpp>

namespace lte
{
namespace enb
{

ZMQClient::ZMQClient() :
    context_(zmq::context_t(1)), socket_(zmq::socket_t(context_, ZMQ_DEALER))
{
    socket_.connect ("tcp://*:5556");
}

void ZMQClient::send(std::unique_ptr<util::Message> msg)
{
    std::string message;
    msg->SerializeToString(&message);
        
    zmq::message_t result(message.size());
    memcpy((void*)result.data(),  message.c_str(), message.size());
        
    dbg() << "Sending: \n" << *msg;
    socket_.send (result);
}

std::unique_ptr< util::Message > ZMQClient::receive()
{
    zmq::message_t request;
    socket_.recv (&request);
    Deserializer deserializer;
    auto result = deserializer.deserialize(request);
    
    if(result != nullptr)
    {
        dbg() << "Received: \n" << *result;
    }else{
        err() << "Message was not decoded properly";
    }
    
    return result;
}

ZMQClient::~ZMQClient()
{
    socket_.close();
}

}
}