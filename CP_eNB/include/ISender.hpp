#pragma once
#include "Controller.hpp"

namespace lte
{
namespace enb
{

template<class T>
class ISender{
public:
    virtual ~ISender(){}
    virtual void send(const T&) = 0;
};

    
}
}