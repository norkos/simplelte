#pragma once

namespace lte
{
namespace util
{

class ITimerWatcher;

class ITimer
{
public:
    virtual ~ITimer() = default;
    virtual void subscribe(ITimerWatcher& watcher, int time_out) = 0;
    virtual void unsubscribe(ITimerWatcher& watcher) = 0;
};
}
}