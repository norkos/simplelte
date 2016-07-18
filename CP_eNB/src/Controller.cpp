#include "Controller.hpp"

namespace lte
{
namespace enb
{

void Controller::handle_attach_req(const AttachReq& attach_req)
{
    auto context = UeContext{ attach_req.id() };
    ue_manager_->add_ue(std::make_unique<UeContext>(context));
}

void Controller::handle_detach_req(const DetachReq& detach_req)
{
    ue_manager_->remove_ue(detach_req.id());
}
}
}