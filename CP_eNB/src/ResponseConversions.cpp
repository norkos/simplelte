#include <messages.pb.h>
#include "Message.hpp"

namespace lte
{
namespace enb
{

template<>  
Message<AttachResp>::operator std::unique_ptr<lte::util::Message>() const
{
  auto response = std::make_unique<MessageWrapper>();
  response->set_allocated_attach_resp(new AttachResp(payload_));
  return response;
}

template<>
Message<DetachResp>::operator std::unique_ptr<lte::util::Message>() const
{
  auto response = std::make_unique<MessageWrapper>();
  response->set_allocated_detach_resp(new DetachResp(payload_));
  return response;
}

}
}