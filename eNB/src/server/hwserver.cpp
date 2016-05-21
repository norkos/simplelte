#include <zmq.hpp>
#include <string>
#include <iostream>
#include <messages.pb.h>
#include <typeindex>
#include <google/protobuf/text_format.h>
#include <unordered_map>  // std::unordered_map

#include "serialize.hpp"

typedef ::google::protobuf::Message Message;


class HandlerFunctionBase{
public:
    virtual ~HandlerFunctionBase() {}
    virtual void execute(const Message*) = 0;
};

template<class T, class MessageT>
class MemberFunctionHandler : public HandlerFunctionBase{
public:
    typedef void (T::*MemeberFun)(MessageT*);
    MemberFunctionHandler(T* instance,  MemeberFun memFun) : _instance(instance), _function(memFun)
    {}
    
private:
    virtual void execute(const Message* msg)
    {
        (_instance->*_function)(static_cast<MessageT*>(msg));
    }
    T* _instance;
    MemeberFun _function;
};

class MessageHandler{
public:
    ~MessageHandler()
    {
         Handlers::iterator it = _handlers.begin();
         while(it != _handlers.end())
         {
             delete it->second;
             ++it;
         }
         _handlers.clear();
    }
    void handleMessage(const Message* msg)
    {
        Handlers::iterator it = _handlers.find(typeid(*msg));
        if(it != _handlers.end())
        {
            it->second->execute(msg);
        }
    }
    
    template<class T, class MessageT>
    void registerMessageFunc(T* obj, void(T::*memFn)(MessageT*))
    {
        _handlers[typeid(MessageT)] = new MemberFunctionHandler<T, MessageT>(obj, memFn);
    }
    
private:
    typedef std::unordered_map<std::type_index, HandlerFunctionBase*> Handlers;
    Handlers _handlers;
};

class Printer : public MessageHandler{
    
public:
 
    Printer() 
    {
        registerMessageFunc(this, &Printer::onAttachRequest);
        registerMessageFunc(this, &Printer::onAttachResponse);
    }
    
    void onAttachRequest(const lte::AttachReq * attach_req)
    {
        std::string result;
        google::protobuf::TextFormat::PrintToString(*attach_req, &result);
        std::cout << result << std::endl;
    }
    
    void onAttachResponse(const lte::AttachResp * attach_resp)
    {
        std::cout << "Server sends AttachResp" <<  std::endl;
    }
    
};

int main () 
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PAIR);
    socket.bind ("tcp://*:5555");
    Printer printer;

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        std::cout << "Server recives AttachReq" << std::endl;
        
        const lte::AttachReq& attach_req =  deserialize<lte::AttachReq>(request);
        
        printer.handleMessage(&attach_req);
        
        
        lte::AttachResp attach_resp;
        attach_resp.set_id(attach_req.id());
        
        std::string message;
        attach_resp.SerializeToString(&message);
    
        zmq::message_t response(message.size());
        memcpy((void*)response.data(),  message.c_str(), message.size());
        
        printer.handleMessage(&attach_resp);
        socket.send (response);
    }
    return 0;
}
