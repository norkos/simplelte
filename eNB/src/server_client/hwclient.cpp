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

    std::cout << "Connecting" << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
        lte::AttachReq attach_req;
        attach_req.set_id(request_nbr);
        
        std::string message;
        attach_req.SerializeToString(&message);
    
        zmq::message_t request(message.size());
        memcpy((void*)request.data(),  message.c_str(), message.size());
        
         std::cout << "Client sends AttachReq" << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);
        
         const lte::AttachResp& attach_resp =  deserialize<lte::AttachResp>(reply);
        
          std::cout << "Client sends AttachReq" << std::endl;
        std::string result;
        google::protobuf::TextFormat::PrintToString(attach_resp, &result);
        std::cout << result << std::endl;
    }
    return 0;
}