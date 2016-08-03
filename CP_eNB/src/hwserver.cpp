#include <zmq.hpp>
#include <string>
#include <iostream>
#include <MessageHandler.hpp>
#include <Message.hpp>
#include <messages.pb.h>
#include <typeindex>
#include <google/protobuf/text_format.h>
#include <unordered_map>

#include "Controller.hpp"
#include "Sender.hpp"

#include <memory>
#include <iostream>


using namespace lte::enb;
std::unique_ptr<lte::util::Message> deserialize(zmq::message_t& message)
{
    lte::MessageWrapper result;
    std::string msg_str(static_cast<char*>(message.data()),message.size());
    result.ParseFromString(msg_str);
    
    if(result.msg_case() == lte::MessageWrapper::kAttachReq)
    {
        return std::unique_ptr<lte::AttachReq>(std::move(result.release_attach_req()));
    }
    
    if(result.msg_case() == lte::MessageWrapper::kDetachReq)
    {
        return std::unique_ptr<lte::DetachReq>(std::move(result.release_detach_req()));
    }
    
    return nullptr;
}




class UeManager : public IUeManager 
{
public:
    void add_ue(std::unique_ptr<UeContext> ue) {}
    void remove_ue(int ue_id) {}
};


class Dispatcher : public lte::util::MessageHandler<lte::util::Message>
{
public:
    Dispatcher(std::shared_ptr<ISender> sender): controller_(std::make_shared<UeManager>(), sender)
    {
        registerMessage(controller_, &Controller::handle_attach_req);
        registerMessage(controller_, &Controller::handle_detach_req);
    }
    
    Controller controller_;
};


class Listener
{
public:

    Listener(zmq::socket_t& socket, std::shared_ptr<ISender> sender): socket_(socket), dispatcher_(sender) {}
    
    void listen()
    {
        zmq::message_t request;

        //  Wait for next request from client
        socket_.recv (&request);
        
       auto message = std::move(deserialize(request));
       dispatcher_.handleMessage(*message);
    }
    
    zmq::socket_t& socket_;
    Dispatcher dispatcher_;
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
