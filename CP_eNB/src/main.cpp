#include <memory>

#include "Listener.hpp"
#include "UeManager.hpp"
#include "ZMQCommunicationFactory.hpp"
#include <Logger.hpp>

int main () 
{
    using namespace lte::enb;

    lte::dbg() << "Startup";
    auto ue_manager = std::make_unique<UeManager>();
    auto server = ZMQCommunicationFactory().createServer();
    Listener listener(*ue_manager, *server);
    while (true) {
        listener.listen();
    }

    return 0;
}
