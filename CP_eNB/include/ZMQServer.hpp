#pragma once
#include <zmq.hpp>
#include "IServer.hpp"

namespace lte
{
namespace enb
{

class ZMQServer : public IServer
{
public:
    ZMQServer();
    
    ZMQServer(ZMQServer&& server) = delete;
    ZMQServer(const ZMQServer&) = delete;
    ZMQServer& operator=(const ZMQServer&) = delete;
    
    virtual ~ZMQServer();
    void send(std::unique_ptr<util::Message>) override;
    std::unique_ptr<util::Message> receive() override;
    
private:
    zmq::context_t context_;
    zmq::socket_t socket_;
};

}
}