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
    
    virtual ~ZMQServer() = default;
    virtual void send(std::unique_ptr<util::Message>);
    virtual std::unique_ptr<util::Message> receive();
    
private:
    zmq::context_t context_;
    zmq::socket_t socket_;
};

}
}