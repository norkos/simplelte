#pragma once

#include <gmock/gmock.h>
#include <Message.hpp>
#include "ISender.hpp"

namespace lte
{
namespace enb
{
namespace ut
{

class MockSender : public ISender
{
public:
    
    virtual void send(std::unique_ptr<lte::util::Message> ptr) {
        send_proxy(ptr.get());
    }
    
    MOCK_METHOD1(send_proxy, void(lte::util::Message*));
    
};
}
}
}