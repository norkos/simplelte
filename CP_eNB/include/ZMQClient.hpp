#pragma once
#include <zmq.hpp>
#include <memory>
#include "IClient.hpp"

namespace lte
{
namespace enb
{

class ZMQClient : public IClient
{
public:
    ZMQClient();
    
    ZMQClient(ZMQClient&& server) = delete;
    ZMQClient(const ZMQClient&) = delete;
    ZMQClient& operator=(const ZMQClient&) = delete;
    
    virtual ~ZMQClient();
    void send(std::unique_ptr<util::Message>) override;
    std::unique_ptr<util::Message> receive() override;
    bool connect(int port) override;
    
private:
    std::unique_ptr<zmq::context_t> context_;
    std::unique_ptr<zmq::socket_t> socket_;
};

}
}