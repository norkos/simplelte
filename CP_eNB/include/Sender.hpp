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
    virtual ~Sender() = default;
    void send(std::unique_ptr<util::Message> msg) override;

private:  
    zmq::socket_t& socket_;
};

}
}