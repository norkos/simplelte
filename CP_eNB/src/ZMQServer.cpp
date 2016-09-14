#include "ZMQServer.hpp"
#include "Deserializer.hpp"
#include <Logger.hpp>

namespace lte
{
namespace enb
{

ZMQServer::ZMQServer(): 
    context_(zmq::context_t(1)), 
    socket_(zmq::socket_t(context_, ZMQ_PAIR))
{
    socket_.bind ("tcp://*:5555");
    dbg() << "Server created";
}

void ZMQServer::send(std::unique_ptr<util::Message> msg)
{
    std::string message;
    msg->SerializeToString(&message);
        
    zmq::message_t result(message.size());
    memcpy((void*)result.data(),  message.c_str(), message.size());
        
    dbg() << "Sending: " << *msg;
    socket_.send (result);
}

std::unique_ptr< util::Message > ZMQServer::receive()
{
    dbg() << "Waiting for the message";
    zmq::message_t request;
    socket_.recv (&request);
    
    Deserializer deserializer;
    return deserializer.deserialize(request);
}
    
}
}