#pragma once

#include <rrc.pb.h>
#include <s1ap.pb.h>
#include <nas.pb.h>
#include <memory>
#include <ITimer.hpp>
#include <unordered_map>

namespace lte
{
namespace enb
{

class IUeManager;
class IServer;
class IClient;

class Controller{
    
public:
    Controller(IUeManager& ue_manager, IServer& sender);
    ~Controller();
    
    //  new
    void handle_attach_req(const s1ap::AttachReq& attach_req);
    void handle_detach_req(const s1ap::DetachReq& detach_req);
    void handle_dl_throughput(const nas::DownlinkThr& dl_througput);

private:
    bool connect_ue(int ue_id, int port);
    bool disconnect_ue(int ue_id);
    
protected:
    IUeManager& ue_manager_;
    IServer& sender_;
    std::unordered_map<int, std::shared_ptr<IClient>> ues_;
};

}
}