#include "Controller.hpp"

namespace lte
{
namespace eNB
{

void Controller::handle_attach_req(const lte::AttachReq& attach_req)
{
    auto context = UeContext{ attach_req.id() };
    ues[context.id] = context;
}

bool Controller::is_ue_attached(int ue_id)
{
    auto it = ues.find(ue_id);
    return it != ues.end();
}
}
}