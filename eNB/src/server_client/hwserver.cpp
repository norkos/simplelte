#include <zmq.hpp>
#include <string>
#include <iostream>
#include <messages.pb.h>
#include <google/protobuf/text_format.h>

#include "serialize.hpp"

int main () 
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PAIR);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        std::cout << "Server recives AttachReq" << std::endl;
        
        const lte::AttachReq& attach_req =  deserialize<lte::AttachReq>(request);
        
        std::string result;
        google::protobuf::TextFormat::PrintToString(attach_req, &result);
        std::cout << result << std::endl;
        
        
        lte::AttachResp attach_resp;
        attach_resp.set_id(attach_req.id());
        
        std::string message;
        attach_resp.SerializeToString(&message);
    
        zmq::message_t response(message.size());
        memcpy((void*)response.data(),  message.c_str(), message.size());
        
        std::cout << "Server sends AttachResp" <<  std::endl;
        socket.send (response);
    }
    return 0;
}
