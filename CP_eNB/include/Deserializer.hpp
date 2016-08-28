#pragma once
#include "MessageTraits.hpp"
#include <memory>

namespace lte
{
namespace enb
{

namespace
{
template<typename T, typename... Msgs>    
class DeserializerImp{

using UniqueMessage = std::unique_ptr<util::Message>;

public:
    UniqueMessage deserialize(zmq::message_t& message)
    {
        ASN1 result;
        std::string msg_str(static_cast<char*>(message.data()),message.size());
        result.ParseFromString(msg_str);
        
        return extract_proper_message(result);
    }
    
private:
    
    using WrapperTrait = MessageTraits<T>;
    using Wrapper = typename MessageTraits<T>::type;

    UniqueMessage extract_proper_message(ASN1& message)
    {
        if(message.has_rrc())
        {
            auto wrapper = std::unique_ptr<Wrapper>((message.*WrapperTrait::from)());
            return deserializeImp<Msgs...>(*wrapper);
        }
       
        return nullptr;
    }
    
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
        return (wrapper.*Traits::exists)();
    }
    
    template<typename Traits>
    std::unique_ptr<util::Message> create_msg(Wrapper& wrapper)
    {
        return std::unique_ptr<typename Traits::type>(std::move((wrapper.*Traits::from)()));
    }
};
}

using Deserializer = DeserializerImp<rrc::RRC, rrc::AttachReq, rrc::DetachReq>;
}
}