#pragma once
#include <memory>
#include <zmq.hpp>

#include <MessageHandler.hpp>
#include "IListener.hpp"

#include <MessageBase.hpp>

namespace lte
{
namespace enb
{

class ISender;
class IUeManager;
class Controller;

class Listener : public IListener, public lte::util::MessageHandler<lte::util::Message>
{

public:
    Listener(zmq::socket_t& socket, std::shared_ptr<ISender> sender, std::shared_ptr<IUeManager> ue_manager);
    
    Listener(const Listener&) = delete;
    Listener operator=(const Listener&) = delete;
    
    virtual ~Listener();
    virtual void listen();
  
private:
    zmq::socket_t& socket_;
    std::unique_ptr<Controller> controller_;
};

}
}
