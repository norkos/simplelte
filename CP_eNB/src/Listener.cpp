#include "Listener.hpp"
#include "Controller.hpp"
#include "Timer.hpp"
#include "IServer.hpp"
#include <Logger.hpp>

namespace lte
{
namespace enb
{

Listener::Listener(IUeManager& ue_manager, IServer& server): 
            server_(server), timer_(std::make_unique<Timer>()),  
            controller_(std::make_unique<Controller>(ue_manager, server_, *timer_))
{
    registerMessage(*controller_, &Controller::handle_attach_req);
    registerMessage(*controller_, &Controller::handle_detach_req);
    registerMessage(*controller_, &Controller::handle_timer_ind);   
}

void Listener::listen()
{
  dbg() << "Listening";
  auto message = server_.receive();
  if(message == nullptr)
  {
      err() << "Received message which was not decoded properly";
      return;
  }
  dbg() << "Received: " << *message;
  handleMessage(*message);
}

Listener::~Listener()
{
}
}
}