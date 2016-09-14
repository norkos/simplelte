#pragma once
#include <zmq.hpp>

#include <MessageHandler.hpp>
#include <ITimer.hpp>
#include <MessageBase.hpp>

namespace lte
{
namespace enb
{

class ISender;
class IUeManager;
class IServer;
class Controller;

class Listener : public util::MessageHandler<util::Message>
{

public:
    Listener(IUeManager& ue_manager, IServer& server);
    
    Listener(const Listener&) = delete;
    Listener& operator=(const Listener&) = delete;
    
    virtual ~Listener();
    void listen();
  
private:
    IServer& server_;
    std::unique_ptr<util::ITimer> timer_;
    std::unique_ptr<Controller> controller_;
};

}
}
