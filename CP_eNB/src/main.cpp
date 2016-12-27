#include <memory>

#include "Listener.hpp"
#include "ZMQCommunicationFactory.hpp"

#include <Logger.hpp>


int main () 
{
    using namespace lte::enb;
    using namespace lte::util;

    dbg() << "Starting application";
    std::unique_ptr<ICommunicationFactory> factory = std::make_unique<ZMQCommunicationFactory>();
    Listener listener(*factory);
    listener.run();
    
    google::protobuf::ShutdownProtobufLibrary();
    dbg() << "Closing application";
    return 0;
}
