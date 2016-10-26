#pragma once
#include "MessageTraits.hpp"
#include <memory>
#include <lte.pb.h>
#include <Logger.hpp>

namespace lte
{
namespace enb
{

class Deserializer
{
    using UniqueMessage = std::unique_ptr<util::Message>;
    
public:
    UniqueMessage deserialize(zmq::message_t& message)
    {
        ASN1 result;
        std::string msg_str(static_cast<char*>(message.data()),message.size());
        result.ParseFromString(msg_str);
        
        return extract_message(result);
    }
private:
    UniqueMessage extract_message(ASN1& message)
    {
        if(message.has_rrc())
        {
            return rrc_deserializer_.extract_proper_message(message);
        }
        
        if(message.has_s1ap())
        {
             return s1ap_deserializer_.extract_proper_message(message);
        }
        
        return nullptr;
    }
    
    template<typename MessageType, typename... Msgs> 
    struct TypedDeserializer
    {
    public:
        using WrapperTrait = MessageTraits<MessageType>;
        using Wrapper = typename MessageTraits<MessageType>::type;
    
        UniqueMessage extract_proper_message(ASN1& message){
            auto wrapper = std::unique_ptr<Wrapper>((message.*WrapperTrait::from)());
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
            return (wrapper.*Traits::exists)();
        }
        
        template<typename Traits>
        std::unique_ptr<util::Message> create_msg(Wrapper& wrapper)
        {
            return std::unique_ptr<typename Traits::type>(std::move((wrapper.*Traits::from)()));
        }
    };
    
    TypedDeserializer<rrc::RRC, 
                      rrc::AttachResp, rrc::DetachReq> rrc_deserializer_; //todo memory improvement ;)

    TypedDeserializer<s1ap::S1AP, 
                      s1ap::AttachReq> s1ap_deserializer_;
};
}
}