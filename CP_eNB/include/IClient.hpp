#pragma once
#include <memory>
#include <MessageBase.hpp>

namespace lte
{
namespace enb
{

class IClient
{
public:
    virtual ~IClient() = default;
    virtual void send(std::unique_ptr<util::Message>) = 0;
    virtual std::unique_ptr<util::Message> receive() = 0;
    virtual bool connect(int port) = 0;
};

}
}