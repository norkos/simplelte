#pragma once
#include <memory>
#include <zmq.hpp>
#include "IListener.hpp"

#include "IUeManager.hpp"
#include "Controller.hpp"
#include <MessageHandler.hpp>

namespace lte
{
namespace enb
{

class UeManager : public IUeManager 
{
public:
    void add_ue(std::unique_ptr<UeContext> ue) {}
    void remove_ue(int ue_id) {}
};

class Dispatcher : public lte::util::MessageHandler<lte::util::Message>
{
public:
    Dispatcher(std::shared_ptr<ISender> sender): controller_(std::make_shared<UeManager>(), sender)
    {
        registerMessage(controller_, &Controller::handle_attach_req);
        registerMessage(controller_, &Controller::handle_detach_req);
    }
    
    Controller controller_;
};

class Listener : public IListener
{
public:
  Listener(zmq::socket_t& socket, std::shared_ptr<ISender> sender): socket_(socket), dispatcher_(sender) {}
  virtual ~Listener(){}
  virtual void listen();
  
private:
  zmq::socket_t& socket_;
  Dispatcher dispatcher_;
};

}
}
