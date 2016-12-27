#include <Logger.hpp>
#include "Controller.hpp"
#include "Message.hpp"

#include "IUeManager.hpp"
#include "ICommunicationFactory.hpp"
#include "UeContext.hpp"

#include "IServer.hpp"

namespace lte
{
namespace enb
{

Controller::Controller(IServer& sender, ICommunicationFactory& communication_factory):
    sender_(sender), communication_factory_(communication_factory), is_running_(true)
{
}

bool Controller::is_running()
{
    return is_running_;
}

bool Controller::connect_ue(int ue_id, int port)
{   
    auto ue = communication_factory_.createClient();
    
    if(! ue->connect(port))
    {
        err() << "Ue: " << ue_id << " for port: " << port << " was not connected";
        return false;
    }
    
    Message<rrc::AttachReq> request;
    request->set_id(ue_id);
    ue->send(request);
    
    auto message = ue->receive();
    const rrc::AttachResp* resp =  static_cast<rrc::AttachResp*>(message.get());
    ues_[ue_id] = {std::move(ue)};
    
    return resp->status() == rrc::AttachResp_Status_OK;
}

bool Controller::disconnect_ue(int ue_id)
{
    auto ue = ues_[ue_id];
    
    Message<rrc::DetachReq> request;
    request->set_id(ue_id);
    ue->send(request);
    
    auto message = ue->receive();
    const rrc::DetachResp* resp =  static_cast<rrc::DetachResp*>(message.get());
    
    ues_.erase(ue_id);
    return resp->status() == rrc::DetachResp_Status_OK;
}

void Controller::handle_shutdown_ind(const s1ap::ShutdownInd& shutdown_ind)
{
    dbg() << "Processing: ShutdownInd";
    is_running_ = false;
}

void Controller::handle_dl_throughput(const nas::DownlinkThr& dl_througput)
{
    dbg() << "Processing: DownlinkThr";
    
    Message<nas::DownlinkThr> nas;
    nas->set_id(dl_througput.id());
    nas->set_data(dl_througput.data());
    
    ues_[dl_througput.id()]->send(nas);
}

void Controller::handle_attach_req(const s1ap::AttachReq& attach_req)
{
    dbg() << "Processing S1::AttachReq";
    bool connected_ue = connect_ue(attach_req.id(), attach_req.port());
    
    Message<s1ap::AttachResp> response;
    response->set_id(attach_req.id());
    response->set_status(connected_ue ? s1ap::AttachResp::OK : s1ap::AttachResp::NOK);
    
    sender_.send(response);
}

void Controller::handle_detach_req(const s1ap::DetachReq& detach_req)
{
    dbg() << "Processing S1::DetachReq";
    
    bool deataech_ue = disconnect_ue(detach_req.id());
    
    Message<s1ap::DetachResp> response;
    response->set_id(detach_req.id());
    response->set_status(deataech_ue ? s1ap::DetachResp::OK : s1ap::DetachResp::NOK);
    
    sender_.send(response);
}

Controller::~Controller()
{
}

}
}