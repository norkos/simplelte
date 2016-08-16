#pragma once
namespace lte
{
namespace util
{

class ITimerWatcher
{
public:
    virtual ~ITimerWatcher() = default;
    virtual void notify() = 0;
};
}
}