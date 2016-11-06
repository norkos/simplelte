#include "ZMQClient.hpp"
#include "Deserializer.hpp"
#include "FileHandlers.hpp"
#include <Logger.hpp>

namespace lte
{
namespace enb
{

ZMQClient::ZMQClient() 
{
    dbg() << "Before context ";
    showFDInfo();
    context_.reset(new zmq::context_t(1));
        
    dbg() << "Before socket ";
    showFDInfo();
    
    socket_.reset(new zmq::socket_t(*context_, ZMQ_DEALER));
    
    dbg() << "After socket ";
    showFDInfo();
}

bool ZMQClient::connect(int port)
{
    const std::string connection = "tcp://localhost:" + std::to_string(port);
    try{
        dbg() << "Before connecting: " << connection;
        showFDInfo();
        socket_->connect (connection.c_str());
        dbg() << "After connecting: " << connection;
        showFDInfo();
    } catch( std::exception& e)
    {
        err() << "Error for connection string [" << connection << "]: " << e.what();
        return false;
    }
    return true;
}

void ZMQClient::send(std::unique_ptr<util::Message> msg)
{
    std::string message;
    msg->SerializeToString(&message);
        
    zmq::message_t result(message.size());
    memcpy((void*)result.data(),  message.c_str(), message.size());
        
    dbg() << "Sending: \n" << *msg;
    socket_->send (result);
}

std::unique_ptr< util::Message > ZMQClient::receive()
{
    zmq::message_t request;
    socket_->recv (&request);
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
    socket_->close();
}

}
}