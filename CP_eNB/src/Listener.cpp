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

Listener::Listener(ICommunicationFactory& communication): 
            server_(communication.createServer()),  
            controller_(std::make_unique<Controller>(*server_, communication))
{    
    registerMessage(*controller_, &Controller::handle_attach_req);
    registerMessage(*controller_, &Controller::handle_detach_req);
    registerMessage(*controller_, &Controller::handle_dl_throughput);
    registerMessage(*controller_, &Controller::handle_shutdown_ind);
}

void Listener::run()
{
  while(controller_->is_running())
  {
    dbg() << "Listening";
    auto message = server_->receive();

    if(message == nullptr)
    {
        err() << "Skipping handling of not known message";
        continue;
    }
    
    if(!handleMessage(*message))
    {
        err() << "Message not handled properly: "<< *message;
    }
  }
}


Listener::~Listener()
{
}
}
}