#include "Listener.hpp"
#include "Controller.hpp"
#include "Timer.hpp"
#include "IServer.hpp"
#include <Logger.hpp>

#include "ICommunicationFactory.hpp"
namespace lte
{
namespace enb
{

Listener::Listener(IUeManager& ue_manager, ICommunicationFactory& communication): 
            server_(communication.createServer()),  
            controller_(std::make_unique<Controller>(ue_manager, *server_))
{
    registerMessage(*controller_, &Controller::handle_s1_attach_req);
    registerMessage(*controller_, &Controller::handle_attach_req);
    registerMessage(*controller_, &Controller::handle_detach_req);
    registerMessage(*controller_, &Controller::handle_dl_throughput);
}

void Listener::listen()
{
  dbg() << "Listening";
  auto message = server_->receive();
  if(message == nullptr)
  {
      err() << "Skipping handling of not known message";
      return;
  }
  handleMessage(*message);
}

Listener::~Listener()
{
}
}
}