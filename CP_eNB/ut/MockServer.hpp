#pragma once

#include <gmock/gmock.h>
#include <Message.hpp>
#include "IServer.hpp"

namespace lte
{
namespace enb
{
namespace ut
{

class MockServer : public IServer
{
public:
    
    void send(std::unique_ptr<lte::util::Message> ptr) {
        send_proxy(ptr.get());
    }
    
    std::unique_ptr<lte::util::Message> receive() {
        return nullptr;
    }
    
    MOCK_METHOD1(send_proxy, void(lte::util::Message*));
    
};
}
}
}