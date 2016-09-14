#include "ZMQCommunicationFactory.hpp"
#include "ZMQServer.hpp"

namespace lte
{
namespace enb
{

std::unique_ptr<IServer> ZMQCommunicationFactory::createServer()
{
    return std::make_unique<ZMQServer>();
}

}
}