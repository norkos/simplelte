#include "Listener.hpp"
#include "Deserializer.hpp"
#include "Controller.hpp"
#include "Timer.hpp"
#include <Logger.hpp>

namespace lte
{
namespace enb
{

Listener::Listener(zmq::socket_t& socket, ISender& sender, IUeManager& ue_manager): 
            socket_(socket), timer_(std::make_unique<Timer>()), 
            controller_(std::make_unique<Controller>(ue_manager, sender, *timer_))
{
    registerMessage(*controller_, &Controller::handle_attach_req);
    registerMessage(*controller_, &Controller::handle_detach_req);
    registerMessage(*controller_, &Controller::handle_timer_ind);
}

void Listener::listen()
{
  zmq::message_t request;
  socket_.recv (&request);
  
  Deserializer deserializer;
  auto message = std::move(deserializer.deserialize(request));
  if(message == nullptr)
  {
      //err() << "Received message which was not decoded properly";
      return;
  }
  //dbg() << "Received: " << *message;
  handleMessage(*message);
}

Listener::~Listener()
{
}
}
}