#pragma once

#include <rrc.pb.h>
#include <memory>

namespace lte
{
namespace enb
{
    
class IUeManager;
class ISender;

class Controller{
    
public:
    Controller(std::shared_ptr<IUeManager> ue_manager, std::shared_ptr<ISender> sender)
        :ue_manager_(ue_manager), sender_(sender)
    {}
    
    void handle_attach_req(const rrc::AttachReq& attach_req);
    void handle_detach_req(const rrc::DetachReq& detach_req);

private:
    std::shared_ptr<IUeManager> ue_manager_;
    std::shared_ptr<ISender> sender_;
};

}
}