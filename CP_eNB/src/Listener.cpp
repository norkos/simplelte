#include "Listener.hpp"
#include "Deserializer.hpp"
#include "Controller.hpp"
#include "Timer.hpp"

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
}

void Listener::listen()
{
  zmq::message_t request;

  //  Wait for next request from client
  socket_.recv (&request);
  
  using Wrapper = rrc::RRC;
  using MyDeserializer = Deserializer<Wrapper, rrc::AttachReq, rrc::DetachReq>;
  MyDeserializer deserializer;
  
  auto message = std::move(deserializer.deserialize(request));
  handleMessage(*message);
}

Listener::~Listener()
{
}
}
}