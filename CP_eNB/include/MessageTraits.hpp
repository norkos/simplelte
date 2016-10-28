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
struct MessageTraits<s1ap::S1AP>
{
    using parent = ASN1;
    using type = s1ap::S1AP;
    static constexpr decltype (auto) exists = &ASN1::has_s1ap;
    static constexpr decltype (auto) from = &ASN1::release_s1ap;  
    static constexpr decltype (auto) to = &ASN1::set_allocated_s1ap;
};

template<>
struct MessageTraits<nas::NAS>
{
    using parent = ASN1;
    using type = nas::NAS;
    static constexpr decltype (auto) exists = &ASN1::has_nas;
    static constexpr decltype (auto) from = &ASN1::release_nas;  
    static constexpr decltype (auto) to = &ASN1::set_allocated_nas;
};

template<>
struct MessageTraits<nas::DownlinkThr>
{
    using parent = nas::NAS;
    using type = nas::DownlinkThr;
    static constexpr decltype (auto) exists = &nas::NAS::has_downlink_thr;
    static constexpr decltype (auto) to = &nas::NAS::set_allocated_downlink_thr;
    static constexpr decltype (auto) from = &nas::NAS::release_downlink_thr;
};

template<>
struct MessageTraits<rrc::AttachReq>
{
    using parent = rrc::RRC;
    using type = rrc::AttachReq;
    static constexpr decltype (auto) exists = &rrc::RRC::has_attach_req;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_attach_req;
    static constexpr decltype (auto) from = &rrc::RRC::release_attach_req;
};

template<>
struct MessageTraits<rrc::AttachResp>
{
    using parent = rrc::RRC;
    using type = rrc::AttachResp;
    static constexpr decltype (auto) exists = &rrc::RRC::has_attach_resp;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_attach_resp;
    static constexpr decltype (auto) from = &rrc::RRC::release_attach_resp;
};

template<>
struct MessageTraits<s1ap::AttachReq>
{
    using parent = s1ap::S1AP;
    using type = s1ap::AttachReq;
    static constexpr decltype (auto) exists = &s1ap::S1AP::has_attach_req;
    static constexpr decltype (auto) to = &s1ap::S1AP::set_allocated_attach_req;
    static constexpr decltype (auto) from = &s1ap::S1AP::release_attach_req;  
};

template<>
struct MessageTraits<s1ap::AttachResp>
{
    using parent = s1ap::S1AP;
    using type = s1ap::AttachResp;
    static constexpr decltype (auto) exists = &s1ap::S1AP::has_attach_resp;
    static constexpr decltype (auto) to = &s1ap::S1AP::set_allocated_attach_resp;
    static constexpr decltype (auto) from = &s1ap::S1AP::release_attach_resp;
};

template<>
struct MessageTraits<rrc::DetachReq>
{
    using parent = rrc::RRC;
    using type = rrc::DetachReq;
    static constexpr decltype (auto) exists = &rrc::RRC::has_detach_req;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_detach_req;
    static constexpr decltype (auto) from = &rrc::RRC::release_detach_req;
};

template<>
struct MessageTraits<rrc::DetachResp>
{
    using parent = rrc::RRC;
    using type = rrc::DetachResp;
    static constexpr decltype (auto) exists = &rrc::RRC::has_detach_resp;
    static constexpr decltype (auto) to = &rrc::RRC::set_allocated_detach_resp;
    static constexpr decltype (auto) from = &rrc::RRC::release_detach_resp;
};

template<>
struct MessageTraits<s1ap::DetachReq>
{
    using parent = s1ap::S1AP;
    using type = s1ap::DetachReq;
    static constexpr decltype (auto) exists = &s1ap::S1AP::has_detach_req;
    static constexpr decltype (auto) to = &s1ap::S1AP::set_allocated_detach_req;
    static constexpr decltype (auto) from = &s1ap::S1AP::release_detach_req;
};

template<>
struct MessageTraits<s1ap::DetachResp>
{
    using parent = s1ap::S1AP;
    using type = s1ap::DetachResp;
    static constexpr decltype (auto) exists = &s1ap::S1AP::has_detach_resp;
    static constexpr decltype (auto) to = &s1ap::S1AP::set_allocated_detach_resp;
    static constexpr decltype (auto) from = &s1ap::S1AP::release_detach_resp;
};

}
}