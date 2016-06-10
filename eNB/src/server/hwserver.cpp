#include <zmq.hpp>
#include <string>
#include <iostream>
#include <messages.pb.h>
#include <typeindex>
#include <google/protobuf/text_format.h>
#include <unordered_map>  // std::unordered_map

#include "serialize.hpp"
#include "utils/MessageHandler.hpp"

class Printer : public MessageHandler {
    
public:
 
    Printer() 
    {
    }
    
    void onAttachRequest(const lte::AttachReq * attach_req)
    {
        std::cout << "Server recives AttachReq" << std::endl;
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
