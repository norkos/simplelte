#include "Listener.hpp"
#include "MessageTraits.hpp"

namespace lte
{
namespace enb
{
   
template<typename... Msgs>    
class Deserializer{
public:
    std::unique_ptr<lte::util::Message> deserialize(zmq::message_t& message)
    {
        lte::MessageWrapper result;
        std::string msg_str(static_cast<char*>(message.data()),message.size());
        result.ParseFromString(msg_str);
        
        return deserializeImp<Msgs...>(result);
    }
    
private:
    template<typename Head, typename... Tail>
    typename std::enable_if<(sizeof...(Tail)>0),std::unique_ptr<lte::util::Message>>::type
    deserializeImp(lte::MessageWrapper& wrapper)
    {
        using Traits = MessageTraits<Head>;
        return is_type<Traits>(wrapper) ? create_msg<Traits>(wrapper) : deserializeImp<Tail...>(wrapper);    
    }
    
    template<typename LastElem>
    std::unique_ptr<lte::util::Message> deserializeImp(lte::MessageWrapper& wrapper)
    {
        using Traits = MessageTraits<LastElem>;
        return is_type<Traits>(wrapper) ? create_msg<Traits>(wrapper) : nullptr;
    }
    
    template<typename Traits>
    bool is_type(lte::MessageWrapper& wrapper)
    {
        return wrapper.msg_case() == Traits::id;
    }
    
    template<typename Traits>
    std::unique_ptr<lte::util::Message> create_msg(lte::MessageWrapper& wrapper)
    {
        return std::unique_ptr<typename Traits::type>(std::move((wrapper.*Traits::from)()));
    }
};

Listener::Listener(zmq::socket_t& socket, std::shared_ptr<ISender> sender): 
            socket_(socket), controller_(std::make_shared<UeManager>(), sender)
{
    registerMessage(controller_, &Controller::handle_attach_req);
    registerMessage(controller_, &Controller::handle_detach_req);
}

void Listener::listen()
{
  zmq::message_t request;

  //  Wait for next request from client
  socket_.recv (&request);
  
  using MyDeserializer = Deserializer<AttachReq, DetachReq>;
  MyDeserializer deserializer;
  
  auto message = std::move(deserializer.deserialize(request));
  handleMessage(*message);
}

}
}