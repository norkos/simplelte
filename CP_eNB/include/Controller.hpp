#pragma once

#include <rrc.pb.h>
#include <memory>
#include <ITimer.hpp>

namespace lte
{
namespace enb
{

class IUeManager;
class ISender;

class Controller{
    
public:
    Controller(std::shared_ptr<IUeManager> ue_manager, std::shared_ptr<ISender> sender);
    
    void handle_attach_req(const rrc::AttachReq& attach_req);
    void handle_detach_req(const rrc::DetachReq& detach_req);

private:
    std::shared_ptr<IUeManager> ue_manager_;
    std::shared_ptr<ISender> sender_;
    std::unique_ptr<util::ITimer> timer_;
};

}
}