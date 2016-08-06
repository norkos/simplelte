#pragma once
#include <zmq.hpp>

#include "ISender.hpp"

namespace lte
{
namespace enb
{

class Sender : public ISender
{
public:

    Sender(zmq::socket_t& socket): socket_(socket) {}
    
    void send(std::unique_ptr<lte::util::Message> msg);

private:  
    zmq::socket_t& socket_;
};

}
}