#include <Logger.hpp>
#include "Controller.hpp"
#include "Message.hpp"

#include "IUeManager.hpp"
#include "UeContext.hpp"
#include "SIBService.hpp"

#include "IServer.hpp"

namespace lte
{
namespace enb
{

Controller::Controller(IUeManager& ue_manager, IServer& sender):
    ue_manager_(ue_manager), sender_(sender)
{
}

void Controller::handle_detach_req(const rrc::DetachReq& detach_req)
{
    dbg() << "Processing: DetachReq";
    const auto id = detach_req.id();
    Message<rrc::DetachResp> response;
    response->set_id(id);
    
    if(ue_manager_.remove_ue(id)){
        response->set_status(rrc::DetachResp::OK);
    }else{
        response->set_status(rrc::DetachResp::NOK);
    }
   
    sender_.send(response);
}

void Controller::handle_attach_req(const rrc::AttachReq& attach_req)
{
    dbg() << "Processing: AttachReq";
    const auto id = attach_req.id();
    Message<rrc::AttachResp> response;
    response->set_id(id);
    
    bool is_ue_aleady_attach = ue_manager_.is_ue(id);
    if(is_ue_aleady_attach){
        response->set_status(rrc::AttachResp::NOK);
    }
    else{
        auto context = UeContext{ id };
        ue_manager_.add_ue(std::make_unique<UeContext>(context));
        response->set_status(rrc::AttachResp::OK);
    }
    
    sender_.send(response);
}

Controller::~Controller()
{
}

}
}