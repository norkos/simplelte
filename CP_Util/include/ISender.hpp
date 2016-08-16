#pragma once
#include <MessageBase.hpp>

namespace lte
{
namespace enb
{

class ISender
{
public:
    virtual ~ISender(){}
    virtual void send(std::unique_ptr<lte::util::Message> msg) = 0;
};

}
}