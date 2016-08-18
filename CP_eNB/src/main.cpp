#include <zmq.hpp>
#include <memory>

#include "Listener.hpp"
#include "Sender.hpp"
#include "UeManager.hpp"
#include "Timer.hpp"

int main () 
{
    using namespace lte::enb;
    
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PAIR);
    socket.bind ("tcp://*:5555");

    auto sender = std::make_unique<Sender>(socket);
    auto ue_manager = std::make_unique<UeManager>();
    auto timer = std::make_unique<Timer>();
    Listener listener(socket, *sender, *ue_manager, *timer);
    
    while (true) {
        listener.listen();
    }

    return 0;
}
