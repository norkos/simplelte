#include "Controller.hpp"
#include "Message.hpp"

namespace lte
{
namespace enb
{

void Controller::handle_attach_req(const AttachReq& attach_req)
{
    auto id = attach_req.id();
    auto context = UeContext{ id };
    ue_manager_->add_ue(std::make_unique<UeContext>(context));
    
    auto response = Message<AttachResp>();
    response->set_id(id);
    
    sender_->send(response);
}

void Controller::handle_detach_req(const DetachReq& detach_req)
{
    ue_manager_->remove_ue(detach_req.id());
    
    auto response = Message<DetachResp>();
    response->set_id(detach_req.id());
    response->set_status(DetachResp::OK);

    sender_->send(response);
}
}
}