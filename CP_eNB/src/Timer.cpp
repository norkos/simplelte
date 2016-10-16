#include <chrono>
#include <future>
#include <zmq.hpp>
#include "Timer.hpp"
#include "ITimerWatcher.hpp"

#include "Message.hpp"
#include "IClient.hpp"

#include <Logger.hpp>

namespace lte
{
namespace enb
{

Timer::Timer(std::unique_ptr<IClient> client) : client_(std::move(client)) 
{
}

void Timer::update()
{
    for(auto& i : subscribers_)
    {
        auto& no_const = const_cast<util::ITimerWatcher&>(*i);
        no_const.notify();
    }
}

void Timer::subscribe(const util::ITimerWatcher& watcher, int time_out) 
{
    subscribers_.push_back(&watcher);
    std::thread([this,time_out]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(time_out));
                send();
            }).detach();
}

void Timer::unsubscribe(const util::ITimerWatcher& watcher)
{    
}

void Timer::send()
{
}

}
}