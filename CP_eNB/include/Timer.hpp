#pragma once
#include <ITimer.hpp>

namespace lte
{
namespace enb
{

class Timer : public util::ITimer 
{
public:
    virtual ~Timer() = default;
    virtual void subscribe(util::ITimerWatcher& watcher, int time_out);
    virtual void unsubscribe(util::ITimerWatcher& watcher);
};
}
}