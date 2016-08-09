#pragma once

namespace lte
{
namespace enb
{
class IListener
{
public:
  virtual ~IListener(){}
  virtual void listen() = 0;
};

}
}