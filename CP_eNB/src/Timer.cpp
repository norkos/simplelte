#include <Logger.hpp>
#include "Timer.hpp"
#include "ITimerWatcher.hpp"

#include "Message.hpp"
#include <chrono>
#include <future>

namespace lte
{
namespace enb
{

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
    /**
    subscribers_.push_back(&watcher);
    std::thread([this,time_out]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(time_out));
                send();
            }).detach();
            */
}

void Timer::unsubscribe(const util::ITimerWatcher& watcher)
{    
}

void Timer::send()
{
    /**
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUSH);
    socket.connect ("tcp://localhost:5555");
    Sender sender(socket);
    
    Message<internal::TimerInd> timer;
    sender.send(timer);
    socket.close();
    */
}

}
}