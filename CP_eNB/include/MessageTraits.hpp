#pragma once

namespace lte
{
namespace enb
{

template<typename T>
struct MessageTraits {
};

template<>
struct MessageTraits<lte::AttachReq>
{
    using payload = AttachReq;
    static constexpr auto value = lte::MessageWrapper::kAttachReq;
    static constexpr decltype (auto) from = &lte::MessageWrapper::release_attach_req;  
};

template<>
struct MessageTraits<lte::AttachResp>
{
    using payload = AttachResp;
    static constexpr auto value = lte::MessageWrapper::kAttachResp;
    static constexpr decltype (auto) to = &lte::MessageWrapper::set_allocated_attach_resp;
};

template<>
struct MessageTraits<lte::DetachReq>
{
    using payload = DetachReq;
    static constexpr auto value = lte::MessageWrapper::kDetachReq;
    static constexpr decltype (auto) from = &lte::MessageWrapper::release_detach_req;
    
};

template<>
struct MessageTraits<lte::DetachResp>
{
    using payload = DetachResp;
    static constexpr auto value = lte::MessageWrapper::kDetachResp;
    static constexpr decltype (auto) to = &lte::MessageWrapper::set_allocated_detach_resp;
};



}
}