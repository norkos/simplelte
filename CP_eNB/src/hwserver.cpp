#include <zmq.hpp>
#include <string>
#include <iostream>
#include <MessageHandler.hpp>
#include <Message.hpp>
#include <messages.pb.h>
#include <typeindex>
#include <google/protobuf/text_format.h>
#include <unordered_map>  // std::unordered_map

#include "Controller.hpp"
#include "ISender.hpp"

#include <memory>
#include <iostream>

template<typename MessageType>
MessageType deserialize(zmq::message_t& message)
{
    MessageType result;
    std::string msg_str(static_cast<char*>(message.data()),message.size());
    result.ParseFromString(msg_str);
    return result;
}


using namespace lte::enb;

class UeManager : public IUeManager 
{
public:
    void add_ue(std::unique_ptr<UeContext> ue) {}
    void remove_ue(int ue_id) {}
};


class Dispatcher : public lte::util::MessageHandler<lte::util::Message>
{
public:
    Dispatcher(std::shared_ptr<ISender<lte::util::Message>> sender): controller_(std::make_shared<UeManager>(), sender)
    {
        registerMessage(controller_, &Controller::handle_attach_req);
        registerMessage(controller_, &Controller::handle_detach_req);
    }
    
    Controller controller_;
};


class Listener
{
public:

    Listener(zmq::socket_t& socket, std::shared_ptr<ISender<lte::util::Message>> sender): socket_(socket), dispatcher_(sender) {}
    
    void listen()
    {
        zmq::message_t request;

        //  Wait for next request from client
        socket_.recv (&request);
        
        const lte::AttachReq& attach_req =  deserialize<lte::AttachReq>(request);
        dispatcher_.handleMessage(attach_req);
    }
    
    zmq::socket_t& socket_;
    Dispatcher dispatcher_;
};

class Sender : public ISender<lte::util::Message>
{
public:

    Sender(zmq::socket_t& socket): socket_(socket) {}
    
    void send(const lte::util::Message& msg)
    {
        std::string message;
        msg.SerializeToString(&message);

        zmq::message_t response(message.size());
        memcpy((void*)response.data(),  message.c_str(), message.size());
        
        socket_.send (response);
    }
    
    zmq::socket_t& socket_;
};

int main () 
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PAIR);
    socket.bind ("tcp://*:5555");

    auto sender = std::make_shared<Sender>(socket);
    Listener listener(socket, sender);
    
    while (true) {
        listener.listen();
    }

    return 0;
}
