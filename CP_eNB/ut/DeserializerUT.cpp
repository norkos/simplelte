#include <gtest/gtest.h>
#include <memory>

#include "Deserializer.hpp"

namespace GT = ::testing;

namespace lte
{
namespace enb
{
namespace ut
{

std::unique_ptr<zmq::message_t> create_message(ASN1& wrapper)
{
    std::string message;
    wrapper.SerializeToString(&message);
    
    auto result = std::make_unique<zmq::message_t>(message.size());
    memcpy((void*)result->data(),  message.c_str(), message.size());
    
    return result;
}

template<typename Wrapper, typename Payload>
using FunctionPtr = void(Wrapper::*)(Payload*);

template<typename Wrapper, typename Payload>
std::unique_ptr<ASN1> create_wrapped_message(Payload* msg, 
                                             FunctionPtr<Wrapper, Payload> payload_setter, 
                                             FunctionPtr<ASN1, Wrapper> wrapper_setter)
{
    auto wrapper = new Wrapper();
    (*wrapper.*payload_setter)(msg);
    
    auto result = std::make_unique<ASN1>();
    (*result.*wrapper_setter)(wrapper);
    
    return result;
}

template<typename Payload>
std::unique_ptr<ASN1> create_wrapped_message(Payload* msg, FunctionPtr<rrc::RRC, Payload> payload_setter)
{   
    return create_wrapped_message(msg, payload_setter, &ASN1::set_allocated_rrc);
}

template<typename Payload>
std::unique_ptr<ASN1> create_wrapped_message(Payload* msg, FunctionPtr<s1ap::S1AP, Payload> payload_setter)
{
    return create_wrapped_message(msg, payload_setter, &ASN1::set_allocated_s1ap);
}

TEST(DeserializerRRC, attach_resp)
{
    Deserializer sut;
    
    //  given
    rrc::AttachResp* payload = new rrc::AttachResp();
    payload->set_id(1);
    payload->set_status(rrc::AttachResp_Status_OK);
    auto wrapper = create_wrapped_message(payload, &rrc::RRC::set_allocated_attach_resp);
    auto message = create_message(*wrapper);
    
    //  when
    auto result = sut.deserialize(*message);
    
    //  then
    ASSERT_TRUE(result != nullptr);
    ASSERT_TRUE(typeid(*result) == typeid(*payload));
}

TEST(DeserializerS1AP, attach_req)
{
    Deserializer sut;
    
    //  given
    s1ap::AttachReq* payload = new s1ap::AttachReq();
    payload->set_id(1);
    payload->set_port(1);
    auto wrapper = create_wrapped_message(payload, &s1ap::S1AP::set_allocated_attach_req);
    auto message = create_message(*wrapper);
  
    //  when
    auto result = sut.deserialize(*message);
    
    //  then
    ASSERT_TRUE(result != nullptr);
    ASSERT_TRUE(typeid(*result) == typeid(*payload));
}

}
}
}