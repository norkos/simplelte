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
  
    operator std::unique_ptr<lte::util::Message>() const 
    {
        auto response = std::make_unique<ASN1>();
        auto rrc = std::make_unique<RRC>();
        (*rrc.*MessageTraits<Payload>::to)(new Payload(payload_));
        
        response->set_allocated_rrc(rrc.release());
        return response;
    }
  
private:
  Payload payload_;
};


}
}