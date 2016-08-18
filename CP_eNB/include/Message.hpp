#pragma once
#include <MessageBase.hpp>
#include <memory>
#include <type_traits>

#include "MessageTraits.hpp"

namespace lte
{
namespace enb
{

template<typename Payload>
class Message
{

using Traits = MessageTraits<Payload>;
using WrapperTraits = MessageTraits<typename Traits::parent>;
    
public:
    Payload* operator->() { return &payload_; }
    const Payload* operator->() const { return &payload_; }
    
    operator std::unique_ptr<util::Message>() const 
    {
        return to<typename Traits::parent>();
    }
    
private:   
    
    template <typename Condition>
    using EnableIf = typename std::enable_if_t<Condition::value, std::unique_ptr<util::Message>>;

    template <typename Condition>
    using DisableIf = typename std::enable_if_t<!Condition::value, std::unique_ptr<util::Message>>;

    template<class Parent>
    EnableIf<std::is_same<Parent, ASN1>>
    to() const
    {        
        auto response = std::make_unique<ASN1>();
        (*response.*Traits::to)(new Payload(payload_));
        return response;
    }
    
    template<class Parent>
    DisableIf<std::is_same<Parent, ASN1>>
    to() const 
    {        
        auto wrapper = std::make_unique<typename WrapperTraits::type>();
        (*wrapper.*Traits::to)(new Payload(payload_));
        
        auto response = std::make_unique<ASN1>();
        (*response.*WrapperTraits::to)(wrapper.release());
        return response;
    }
   
   Payload payload_;
};


}
}