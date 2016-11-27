#include <memory>

#include "Listener.hpp"
#include "UeManager.hpp"
#include "ZMQCommunicationFactory.hpp"

#include <Logger.hpp>


int main () 
{
    using namespace lte::enb;
    using namespace lte::util;

    dbg() << "Starting application";
    auto ue_manager = std::make_unique<UeManager>();
    //std::unique_ptr<ICommunicationFactory> factory = std::make_unique<ZMQCommunicationFactory>();
    ICommunicationFactory* factory = new ZMQCommunicationFactory();
    Listener listener(*ue_manager, *factory);
    listener.run();
    
    google::protobuf::ShutdownProtobufLibrary();
    dbg() << "Closing application";
    return 0;
}
