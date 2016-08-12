#pragma once

namespace lte
{
namespace enb
{

template<typename T>
struct Traits {
};

template<>
struct Traits<lte::AttachReq>
{
    using type = lte::AttachReq;
    static constexpr decltype (auto) from = &lte::MessageWrapper::release_attach_req;
    
};

template<>
struct Traits<lte::AttachResp>
{
    using type = lte::AttachResp;
    static constexpr decltype (auto) to = &lte::MessageWrapper::set_allocated_attach_resp;
};

template<>
struct Traits<lte::DetachReq>
{
    using type = lte::DetachReq;
    static constexpr decltype (auto) from = &lte::MessageWrapper::release_detach_req;
    
};

template<>
struct Traits<lte::DetachResp>
{
    using type = lte::DetachResp;
    static constexpr decltype (auto) to = &lte::MessageWrapper::set_allocated_detach_resp;
};


}
}