#pragma once
#include "MessageTraits.hpp"
#include <memory>

namespace lte
{
namespace enb
{

template<typename T, typename... Msgs>    
class Deserializer{

using WrapperTrait = MessageTraits<T>;
using Wrapper = typename MessageTraits<T>::type;

public:
    std::unique_ptr<util::Message> deserialize(zmq::message_t& message)
    {
        ASN1 result;
        std::string msg_str(static_cast<char*>(message.data()),message.size());
        result.ParseFromString(msg_str);
        
        auto wrapper = std::unique_ptr<Wrapper>((result.*WrapperTrait::from)());
        return deserializeImp<Msgs...>(*wrapper);
    }
    
private:
    template<typename Head, typename... Tail>
    typename std::enable_if_t<(sizeof...(Tail)>0),std::unique_ptr<util::Message>>
    deserializeImp(Wrapper& wrapper)
    {
        using Traits = MessageTraits<Head>;
        return is_type<Traits>(wrapper) ? create_msg<Traits>(wrapper) : deserializeImp<Tail...>(wrapper);    
    }
    
    template<typename LastElem>
    std::unique_ptr<util::Message> deserializeImp(Wrapper& wrapper)
    {
        using Traits = MessageTraits<LastElem>;
        return is_type<Traits>(wrapper) ? create_msg<Traits>(wrapper) : nullptr;
    }
    
    template<typename Traits>
    bool is_type(Wrapper& wrapper)
    {
        return wrapper.msg_case() == Traits::id;
    }
    
    template<typename Traits>
    std::unique_ptr<util::Message> create_msg(Wrapper& wrapper)
    {
        return std::unique_ptr<typename Traits::type>(std::move((wrapper.*Traits::from)()));
    }
};
}
}