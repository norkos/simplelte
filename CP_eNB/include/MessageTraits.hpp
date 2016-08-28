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
struct MessageTraits<rrc::RRC>
{
    using parent = ASN1;
    using type = rrc::RRC;
    static constexpr decltype (auto) exists = &ASN1::has_rrc;
    static constexpr decltype (auto) from = &ASN1::release_rrc;  
    static constexpr decltype (auto) to = &ASN1::set_allocated_rrc;
};

template<>
struct MessageTraits<rrc::AttachReq>
{
    using parent = rrc::RRC;
    using type = rrc::AttachReq;
    static constexpr decltype (auto) exists = &rrc::RRC::has_attach_req;
    static constexpr decltype (auto) from = &rrc::RRC::release_attach_req;  
};

template<>
struct MessageTraits<rrc::AttachResp>
{
    using parent = rrc::RRC;
    using type = rrc::AttachResp;
    static constexpr decltype (auto) exists = &rrc::RRC::has_attach_resp;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_attach_resp;
};

template<>
struct MessageTraits<rrc::DetachReq>
{
    using parent = rrc::RRC;
    using type = rrc::DetachReq;
    static constexpr decltype (auto) exists = &rrc::RRC::has_detach_req;
    static constexpr decltype (auto) from = &rrc::RRC::release_detach_req;
    
};

template<>
struct MessageTraits<rrc::DetachResp>
{
    using parent = rrc::RRC;
    using type = rrc::DetachResp;
    static constexpr decltype (auto) exists = &rrc::RRC::has_detach_resp;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_detach_resp;
};

template<>
struct MessageTraits<rrc::SIB>
{
    using parent = rrc::RRC;
    using type = rrc::SIB;
    static constexpr decltype (auto) exists = &rrc::RRC::has_sib;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_sib;
};

template<>
struct MessageTraits<internal::TimerInd>
{
    using parent = ASN1;
    using type = internal::TimerInd;
    static constexpr decltype (auto) exists = &ASN1::has_timerind;
    static constexpr decltype (auto) from = &ASN1::release_timerind;  
    static constexpr decltype (auto) to = &ASN1::set_allocated_timerind;
};

}
}