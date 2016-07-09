#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include <memory>
#include <iostream>

template<typename MessageType>
MessageType deserialize(zmq::message_t& message)
{
    MessageType result;
    std::string msg_str(static_cast<char*>(message.data()),message.size());
    result.ParseFromString(msg_str);
    return result;
}

#endif