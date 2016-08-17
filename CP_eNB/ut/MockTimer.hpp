#pragma once

#include <gmock/gmock.h>
#include <ITimer.hpp>
#include <ITimerWatcher.hpp>

namespace lte
{
namespace enb
{

namespace ut
{
class MockTimer : public util::ITimer
{
public:
    
    MOCK_METHOD0(update, void());
    MOCK_METHOD2(subscribe, void(util::ITimerWatcher&,int));
    MOCK_METHOD1(unsubscribe, void(util::ITimerWatcher&));
    
};
}
}
}