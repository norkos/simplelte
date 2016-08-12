#pragma once
#include <MessageBase.hpp>
#include <memory>

#include "MsgTraits.hpp"

namespace lte
{
namespace enb
{

template<typename Payload>
class Message
{
public:
    Payload* operator->() { return &payload_; }
    const Payload* operator->() const { return &payload_; }
  
    operator std::unique_ptr<lte::util::Message>() const 
    {
        auto response = std::make_unique<MessageWrapper>();
        (*response.*Traits<Payload>::to)(new Payload(payload_));
        return response;
    }
  
private:
  Payload payload_;
};


}
}