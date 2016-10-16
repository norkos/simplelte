#pragma once
#include <zmq.hpp>
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
    
private:
    zmq::context_t context_;
    zmq::socket_t socket_;
};

}
}