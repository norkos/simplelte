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
    virtual void subscribe(const ITimerWatcher& watcher, int time_out) = 0;
    virtual void unsubscribe(const ITimerWatcher& watcher) = 0;
    virtual void update() = 0;
};
}
}