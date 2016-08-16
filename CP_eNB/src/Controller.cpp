#include "Controller.hpp"
#include "Message.hpp"

#include "ISender.hpp"
#include "IUeManager.hpp"
#include "UeContext.hpp"

namespace lte
{
namespace enb
{

void Controller::handle_attach_req(const rrc::AttachReq& attach_req)
{
    const auto id = attach_req.id();
    Message<rrc::AttachResp> response;
    response->set_id(id);
    
    bool is_ue_aleady_attach = ue_manager_->is_ue(id);
    if(is_ue_aleady_attach){
        response->set_status(rrc::AttachResp::NOK);
    }
    else{
        auto context = UeContext{ id };
        ue_manager_->add_ue(std::make_unique<UeContext>(context));
        response->set_status(rrc::AttachResp::OK);
    }
    
    sender_->send(response);
}

void Controller::handle_detach_req(const rrc::DetachReq& detach_req)
{
    const auto id = detach_req.id();
    Message<rrc::DetachResp> response;
    response->set_id(id);
    
    if(ue_manager_->remove_ue(id)){
        response->set_status(rrc::DetachResp::OK);
    }else{
        response->set_status(rrc::DetachResp::NOK);
    }
   
    sender_->send(response);
}
}
}