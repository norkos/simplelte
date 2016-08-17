#pragma once
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

class Listener : public IListener, public util::MessageHandler<util::Message>
{

public:
    Listener(zmq::socket_t& socket, ISender& sender, IUeManager& ue_manager);
    
    Listener(const Listener&) = delete;
    Listener& operator=(const Listener&) = delete;
    
    virtual ~Listener();
    void listen() override;
  
private:
    zmq::socket_t& socket_;
    std::unique_ptr<Controller> controller_;
};

}
}
