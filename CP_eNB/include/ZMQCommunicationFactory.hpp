#pragma once
#include <memory>
#include <zmq.hpp>
#include "ICommunicationFactory.hpp"

namespace lte
{
namespace enb
{

class ZMQCommunicationFactory: public ICommunicationFactory{
public:
    ZMQCommunicationFactory(): context_(zmq::context_t(1)) {}
    virtual ~ZMQCommunicationFactory() = default;
    virtual std::unique_ptr<IServer> createServer();
    virtual std::unique_ptr<IClient> createClient();

private:
    zmq::context_t context_;
};

}
}