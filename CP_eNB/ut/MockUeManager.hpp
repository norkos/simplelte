#pragma once

#include <gmock/gmock.h>
#include "IUeManager.hpp"

namespace lte
{
namespace enb
{
namespace ut
{
class MockUeManager : public IUeManager
{
public:
    virtual void add_ue(std::unique_ptr<UeContext> ptr) {
        add_ue_proxy(ptr.get());
    }
    
    MOCK_METHOD1(add_ue_proxy, void(UeContext*));
    MOCK_METHOD1(remove_ue, void(int));
};
}
}
}