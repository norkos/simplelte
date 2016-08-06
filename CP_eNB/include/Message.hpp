#pragma once
#include <MessageBase.hpp>
#include <memory>

namespace lte
{
namespace enb
{

template<typename Payload>
class Message
{
public:
  Payload* operator->() { return &payload_; }
  const Payload* operator->() const { return &payload_; }
  
  operator std::unique_ptr<lte::util::Message>() const;
  
private:
  Payload payload_;
};


}
}