#pragma once
#include <messages.pb.h>

namespace lte
{
namespace enb
{

template<typename T>
struct MessageTraits {
};

template<>
struct MessageTraits<lte::RRC>
{
    using type = RRC;
    static constexpr auto id = lte::ASN1::kRrc;
    static constexpr decltype (auto) from = &lte::ASN1::release_rrc;  
};

template<>
struct MessageTraits<lte::AttachReq>
{
    using type = AttachReq;
    static constexpr auto id = lte::RRC::kAttachReq;
    static constexpr decltype (auto) from = &lte::RRC::release_attach_req;  
};

template<>
struct MessageTraits<lte::AttachResp>
{
    using type = AttachResp;
    static constexpr auto id = lte::RRC::kAttachResp;
    static constexpr decltype (auto) to = &lte::RRC::set_allocated_attach_resp;
};

template<>
struct MessageTraits<lte::DetachReq>
{
    using type = DetachReq;
    static constexpr auto id = lte::RRC::kDetachReq;
    static constexpr decltype (auto) from = &lte::RRC::release_detach_req;
    
};

template<>
struct MessageTraits<lte::DetachResp>
{
    using type = DetachResp;
    static constexpr auto id = lte::RRC::kDetachResp;
    static constexpr decltype (auto) to = &lte::RRC::set_allocated_detach_resp;
};



}
}