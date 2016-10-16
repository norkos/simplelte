#pragma once
#include <memory>
#include "ICommunicationFactory.hpp"

namespace lte
{
namespace enb
{

class ZMQCommunicationFactory: public ICommunicationFactory{
public:
    virtual ~ZMQCommunicationFactory() = default;
    virtual std::unique_ptr<IServer> createServer();
    virtual std::unique_ptr<IClient> createClient();

};

}
}