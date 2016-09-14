#pragma once
#include <memory>
#include "IServer.hpp"

namespace lte
{
namespace enb
{

class ICommunicationFactory{
public:
    virtual ~ICommunicationFactory() = default;
    virtual std::unique_ptr<IServer> createServer() = 0;
};

}
}