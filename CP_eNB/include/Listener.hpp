#pragma once
#include <zmq.hpp>

#include <MessageHandler.hpp>
#include <ITimer.hpp>
#include <MessageBase.hpp>

namespace lte
{
namespace enb
{

class IUeManager;
class IServer;
class Controller;
class ICommunicationFactory;

class Listener : public util::MessageHandler<util::Message>
{

public:
    Listener(ICommunicationFactory& communication);
    
    Listener(const Listener&) = delete;
    Listener& operator=(const Listener&) = delete;
    
    virtual ~Listener();
    void run();
  
private:
    std::unique_ptr<IServer> server_;
    std::unique_ptr<util::ITimer> timer_;
    std::unique_ptr<Controller> controller_;
};

}
}
