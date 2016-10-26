#pragma once

#include <rrc.pb.h>
#include <s1ap.pb.h>
#include <nas.pb.h>
#include <memory>
#include <ITimer.hpp>

namespace lte
{
namespace enb
{

class IUeManager;
class IServer;

class Controller{
    
public:
    Controller(IUeManager& ue_manager, IServer& sender);
    ~Controller();
    
    void handle_attach_req(const rrc::AttachReq& attach_req);
    void handle_s1_attach_req(const s1ap::AttachReq& attach_req);
    void handle_detach_req(const rrc::DetachReq& detach_req);
    void handle_dl_throughput(const nas::DownlinkThr& dl_througput);

private:
    bool connect_ue(int ue_id, int port);
    
protected:
    IUeManager& ue_manager_;
    IServer& sender_;
};

}
}