#pragma once
#include <ITimer.hpp>
#include <vector>

namespace lte
{
namespace enb
{

class Timer : public util::ITimer 
{
using Subscribers = std::vector<const util::ITimerWatcher*>;

public:
    virtual ~Timer() = default;
    void subscribe(const util::ITimerWatcher& watcher, int time_out) override;
    void unsubscribe(const util::ITimerWatcher& watcher) override;
    void update() override;

private:
    void send();
    Subscribers subscribers_;
};
}
}