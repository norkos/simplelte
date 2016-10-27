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
    auto ue = std::make_unique<ZMQClient>(port);
    
    Message<rrc::AttachReq> request;
    request->set_id(ue_id);
    ue->send(request);
    
    auto message = ue->receive();
    const rrc::AttachResp* resp =  static_cast<rrc::AttachResp*>(message.get());
    ues_[ue_id] = std::move(ue);
    return resp->status() == rrc::AttachResp_Status_OK;
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

Controller::~Controller()
{
}

}
}