#pragma once
#include <Message.hpp>

namespace lte
{
namespace enb
{

class ISender{
public:
    virtual ~ISender(){}
    virtual void send(const lte::util::Message&) = 0;
};

    
}
}