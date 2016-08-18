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
class ISender;
class SIBService;

class Controller{
    
public:
    Controller(IUeManager& ue_manager, ISender& sender);
    ~Controller();
    
    void handle_attach_req(const rrc::AttachReq& attach_req);
    void handle_detach_req(const rrc::DetachReq& detach_req);
    void handle_timer_ind(const internal::TimerInd& timer_ind);

protected:
    IUeManager& ue_manager_;
    ISender& sender_;
    std::unique_ptr<util::ITimer> timer_;
    std::unique_ptr<SIBService> sib_service_;
};

}
}