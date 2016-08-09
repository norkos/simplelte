#pragma once
#include <memory>
#include <zmq.hpp>
#include "IListener.hpp"

#include "UeManager.hpp"
#include "Controller.hpp"
#include <MessageHandler.hpp>

namespace lte
{
namespace enb
{

class Listener : public IListener, public lte::util::MessageHandler<lte::util::Message>
{

public:
    Listener(zmq::socket_t& socket, std::shared_ptr<ISender> sender);
    
    virtual ~Listener(){}
    virtual void listen();
  
private:
    zmq::socket_t& socket_;
    Controller controller_;
};

}
}
