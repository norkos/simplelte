#include "Listener.hpp"

namespace lte
{
namespace enb
{

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

void Listener::listen()
{
  zmq::message_t request;

  //  Wait for next request from client
  socket_.recv (&request);
        
  auto message = std::move(deserialize(request));
  dispatcher_.handleMessage(*message);
}

}
}