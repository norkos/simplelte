#pragma once
#include <ITimer.hpp>

namespace lte
{
namespace enb
{

//template<class TimePolicy>
class Timer : public util::ITimer 
{
public:
    virtual ~Timer() = default;
    void subscribe(util::ITimerWatcher& watcher, int time_out) override;
    void unsubscribe(util::ITimerWatcher& watcher) override;
    void update() override;

private:
//    TimePolicy timer_;
};
}
}