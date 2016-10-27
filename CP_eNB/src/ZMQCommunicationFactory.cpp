#include "ZMQCommunicationFactory.hpp"
#include "ZMQServer.hpp"
#include "ZMQClient.hpp"

namespace lte
{
namespace enb
{

std::unique_ptr<IServer> ZMQCommunicationFactory::createServer()
{
    return std::make_unique<ZMQServer>();
}


std::unique_ptr<IClient> ZMQCommunicationFactory::createClient(int port)
{
    return std::make_unique<ZMQClient>(port);
}

}
}