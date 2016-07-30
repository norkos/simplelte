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
    
    auto response = new AttachResp();
    response->set_id(id);
    
    auto wrapper = MessageWrapper();
    wrapper.set_allocated_attach_resp(response);
    sender_->send(wrapper);
}

void Controller::handle_detach_req(const DetachReq& detach_req)
{
    ue_manager_->remove_ue(detach_req.id());
    
    auto response = new DetachResp();
    response->set_id(detach_req.id());
    response->set_status(DetachResp::OK);

    auto wrapper = MessageWrapper();
    wrapper.set_allocated_detach_resp(response);
    sender_->send(wrapper);
}
}
}