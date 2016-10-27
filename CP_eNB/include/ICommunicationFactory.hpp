#pragma once
#include <memory>
#include "IServer.hpp"
#include "IClient.hpp"

namespace lte
{
namespace enb
{

class ICommunicationFactory{
public:
    virtual ~ICommunicationFactory() = default;
    virtual std::unique_ptr<IServer> createServer() = 0;
    virtual std::unique_ptr<IClient> createClient(int port) = 0;
};

}
}