#include "Controller.hpp"

namespace lte
{
namespace enb
{

void Controller::handle_attach_req(const AttachReq& attach_req)
{
    auto id = attach_req.id();
    auto context = UeContext{ id };
    ue_manager_->add_ue(std::make_unique<UeContext>(context));
    
    auto response = AttachResp();
    response.set_id(id);
    sender_->send(response);
}

void Controller::handle_detach_req(const DetachReq& detach_req)
{
    ue_manager_->remove_ue(detach_req.id());
    
    auto response = DetachResp();
    response.set_id(detach_req.id()+1);
    response.set_status(DetachResp::NOK);
    sender_->send(response);
}
}
}