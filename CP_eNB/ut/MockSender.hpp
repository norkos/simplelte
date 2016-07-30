#pragma once

#include <gmock/gmock.h>
#include <Message.hpp>
#include "ISender.hpp"

namespace lte
{
namespace enb
{
namespace ut
{

class MockSender : public ISender
{
public:
    
    MOCK_METHOD1(send, void(const lte::util::Message&));
    
};
}
}
}