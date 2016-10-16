#include <memory>

#include "Listener.hpp"
#include "UeManager.hpp"
#include "ZMQCommunicationFactory.hpp"

int main () 
{
    using namespace lte::enb;

    auto ue_manager = std::make_unique<UeManager>();
    std::unique_ptr<ICommunicationFactory> factory = std::make_unique<ZMQCommunicationFactory>();
    Listener listener(*ue_manager, *factory);
    while (true) {
        listener.listen();
    }

    return 0;
}
