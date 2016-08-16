#pragma once
#include "MessageTraits.hpp"
#include <memory>

namespace lte
{
namespace enb
{

template<typename... Msgs>    
class Deserializer{
public:
    std::unique_ptr<lte::util::Message> deserialize(zmq::message_t& message)
    {
        lte::ASN1 result;
        std::string msg_str(static_cast<char*>(message.data()),message.size());
        result.ParseFromString(msg_str);
        
        auto rrc = std::unique_ptr<lte::RRC>(result.release_rrc());
        return deserializeImp<Msgs...>(*rrc);
    }
    
private:
    template<typename Head, typename... Tail>
    typename std::enable_if<(sizeof...(Tail)>0),std::unique_ptr<lte::util::Message>>::type
    deserializeImp(lte::RRC& wrapper)
    {
        using Traits = MessageTraits<Head>;
        return is_type<Traits>(wrapper) ? create_msg<Traits>(wrapper) : deserializeImp<Tail...>(wrapper);    
    }
    
    template<typename LastElem>
    std::unique_ptr<lte::util::Message> deserializeImp(lte::RRC& wrapper)
    {
        using Traits = MessageTraits<LastElem>;
        return is_type<Traits>(wrapper) ? create_msg<Traits>(wrapper) : nullptr;
    }
    
    template<typename Traits>
    bool is_type(lte::RRC& wrapper)
    {
        return wrapper.msg_case() == Traits::id;
    }
    
    template<typename Traits>
    std::unique_ptr<lte::util::Message> create_msg(lte::RRC& wrapper)
    {
        return std::unique_ptr<typename Traits::type>(std::move((wrapper.*Traits::from)()));
    }
};
}
}