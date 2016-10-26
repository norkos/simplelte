#include <Logger.hpp>
#include "Controller.hpp"
#include "Message.hpp"

#include "IUeManager.hpp"
#include "UeContext.hpp"

#include "IServer.hpp"

#include "ZMQClient.hpp"

namespace lte
{
namespace enb
{

Controller::Controller(IUeManager& ue_manager, IServer& sender):
    ue_manager_(ue_manager), sender_(sender)
{
}

bool Controller::connect_ue(int ue_id, int port)
{
    ZMQClient client;
    
    Message<rrc::AttachReq> request;
    request->set_id(ue_id);
    client.send(request);
    
    auto message = client.receive();
    const rrc::AttachResp* resp =  static_cast<rrc::AttachResp*>(message.get());
    return resp->status() == rrc::AttachResp_Status_OK;
}

void Controller::handle_s1_attach_req(const s1ap::AttachReq& attach_req)
{
    dbg() << "Processing S1::AttachReq";
    
    bool connected_ue = connect_ue(attach_req.id(), attach_req.port());
    
    Message<s1ap::AttachResp> response;;
    response->set_id(attach_req.id());
    response->set_status(connected_ue ? s1ap::AttachResp::OK : s1ap::AttachResp::NOK);
    
    sender_.send(response);
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

void Controller::handle_dl_throughput(const nas::DownlinkThr& dl_througput)
{
    dbg() << "Processing: DownlinkThr";
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