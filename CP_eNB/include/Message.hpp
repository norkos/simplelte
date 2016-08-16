#pragma once
#include <MessageBase.hpp>
#include <memory>

#include "MessageTraits.hpp"

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
  
    operator std::unique_ptr<util::Message>() const 
    {
        using Traits = MessageTraits<Payload>;
        using ParentTraits = MessageTraits<typename Traits::parent>;
        
        auto wrapper = std::make_unique<typename Traits::parent>();
        (*wrapper.*Traits::to)(new Payload(payload_));
        
        auto response = std::make_unique<ASN1>();
        (*response.*ParentTraits::to)(wrapper.release());
        return response;
    }
  
private:
  Payload payload_;
};


}
}