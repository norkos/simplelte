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
using RRCFunctionPtr = void(Wrapper::*)(Payload*);

template<typename Payload>
std::unique_ptr<ASN1> create_wrapped_rrc_message(Payload* msg, RRCFunctionPtr<rrc::RRC, Payload> setter)
{
    auto rrc = new rrc::RRC();
    (*rrc.*setter)(msg);
    
    auto wrapper = std::make_unique<ASN1>();
    wrapper->set_allocated_rrc(rrc);
    
    return wrapper;
}

template<typename Payload>
std::unique_ptr<ASN1> create_wrapped_s1ap_message(Payload* msg, RRCFunctionPtr<s1ap::S1AP, Payload> setter)
{
    auto s1ap = new s1ap::S1AP();
    (*s1ap.*setter)(msg);
    
    auto wrapper = std::make_unique<ASN1>();
    wrapper->set_allocated_s1ap(s1ap);
    
    return wrapper;
}


TEST(DeserializerRRC, attach_resp)
{
    Deserializer sut;
    
    //  given
    rrc::AttachResp* payload = new rrc::AttachResp();
    payload->set_id(1);
    payload->set_status(rrc::AttachResp_Status_OK);
    auto wrapper = create_wrapped_rrc_message(payload, &rrc::RRC::set_allocated_attach_resp);
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
    auto wrapper = create_wrapped_s1ap_message(payload, &s1ap::S1AP::set_allocated_attach_req);
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