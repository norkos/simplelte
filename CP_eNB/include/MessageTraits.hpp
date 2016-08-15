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
    using type = AttachReq;
    static constexpr auto id = lte::MessageWrapper::kAttachReq;
    static constexpr decltype (auto) from = &lte::MessageWrapper::release_attach_req;  
};

template<>
struct MessageTraits<lte::AttachResp>
{
    using type = AttachResp;
    static constexpr auto id = lte::MessageWrapper::kAttachResp;
    static constexpr decltype (auto) to = &lte::MessageWrapper::set_allocated_attach_resp;
};

template<>
struct MessageTraits<lte::DetachReq>
{
    using type = DetachReq;
    static constexpr auto id = lte::MessageWrapper::kDetachReq;
    static constexpr decltype (auto) from = &lte::MessageWrapper::release_detach_req;
    
};

template<>
struct MessageTraits<lte::DetachResp>
{
    using type = DetachResp;
    static constexpr auto id = lte::MessageWrapper::kDetachResp;
    static constexpr decltype (auto) to = &lte::MessageWrapper::set_allocated_detach_resp;
};



}
}