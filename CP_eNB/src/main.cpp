#include <zmq.hpp>
#include <memory>

#include "Listener.hpp"
#include "Sender.hpp"

int main () 
{
    using namespace lte::enb;
    
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PAIR);
    socket.bind ("tcp://*:5555");

    auto sender = std::make_shared<Sender>(socket);
    Listener listener(socket, sender);
    
    while (true) {
        listener.listen();
    }

    return 0;
}
