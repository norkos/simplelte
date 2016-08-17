#pragma once
#include <lte.pb.h>

namespace lte
{
namespace enb
{

template<typename T>
struct MessageTraits {
};

template<>
struct MessageTraits<internal::TimerInd>
{
    using parent = ASN1;
    using type = internal::TimerInd;
    static constexpr auto id = ASN1::kTimerInd;
    static constexpr decltype (auto) from = &ASN1::release_timerind;  
    static constexpr decltype (auto) to = &ASN1::set_allocated_timerind;
};

template<>
struct MessageTraits<rrc::RRC>
{
    using parent = ASN1;
    using type = rrc::RRC;
    static constexpr auto id = ASN1::kRrc;
    static constexpr decltype (auto) from = &ASN1::release_rrc;  
    static constexpr decltype (auto) to = &ASN1::set_allocated_rrc;
};

template<>
struct MessageTraits<rrc::AttachReq>
{
    using parent = rrc::RRC;
    using type = rrc::AttachReq;
    static constexpr auto id = rrc::RRC::kAttachReq;
    static constexpr decltype (auto) from = &rrc::RRC::release_attach_req;  
};

template<>
struct MessageTraits<rrc::AttachResp>
{
    using parent = rrc::RRC;
    using type = rrc::AttachResp;
    static constexpr auto id = rrc::RRC::kAttachResp;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_attach_resp;
};

template<>
struct MessageTraits<rrc::DetachReq>
{
    using parent = rrc::RRC;
    using type = rrc::DetachReq;
    static constexpr auto id = rrc::RRC::kDetachReq;
    static constexpr decltype (auto) from = &rrc::RRC::release_detach_req;
    
};

template<>
struct MessageTraits<rrc::DetachResp>
{
    using parent = rrc::RRC;
    using type = rrc::DetachResp;
    static constexpr auto id = rrc::RRC::kDetachResp;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_detach_resp;
};



}
}