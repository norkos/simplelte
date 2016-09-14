#pragma once

#include <rrc.pb.h>
#include <internal.pb.h>
#include <memory>
#include <ITimer.hpp>
#include "SIBService.hpp"

namespace lte
{
namespace enb
{

class IUeManager;
class Server;
class SIBService;

class Controller{
    
public:
    Controller(IUeManager& ue_manager, IServer& sender, util::ITimer& timer);
    ~Controller();
    
    void handle_attach_req(const rrc::AttachReq& attach_req);
    void handle_detach_req(const rrc::DetachReq& detach_req);
    void handle_timer_ind(const internal::TimerInd& timer_ind);

protected:
    IUeManager& ue_manager_;
    IServer& sender_;
    util::ITimer& timer_;
    std::unique_ptr<SIBService> sib_service_;
};

}
}