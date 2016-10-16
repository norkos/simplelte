#pragma once
#include <ITimer.hpp>
#include <vector>
#include <Logger.hpp>
namespace lte
{
namespace enb
{

class IClient;

class Timer : public util::ITimer 
{
using Subscribers = std::vector<const util::ITimerWatcher*>;

public:
    Timer(std::unique_ptr<IClient> client);
    virtual ~Timer() = default;
    void subscribe(const util::ITimerWatcher& watcher, int time_out) override;
    void unsubscribe(const util::ITimerWatcher& watcher) override;
    void update() override;

private:
    void send();
    std::unique_ptr<IClient> client_;
    Subscribers subscribers_;
};
}
}