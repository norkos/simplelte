#include "SIBService.hpp"
#include "Message.hpp"
#include "IServer.hpp"
#include <rrc.pb.h>

namespace lte
{
namespace enb
{
void SIBService::notify()
{
    Message<rrc::SIB> indication;
    indication->set_cell_identity(2006);
    sender_.send(indication);
}
}
}