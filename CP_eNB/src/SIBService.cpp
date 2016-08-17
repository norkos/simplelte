#include "SIBService.hpp"
#include "Message.hpp"
#include "ISender.hpp"
#include <internal.pb.h>

namespace lte
{
namespace enb
{
void SIBService::notify()
{
    Message<internal::TimerInd> indication;
    sender_.send(indication);
}
}
}