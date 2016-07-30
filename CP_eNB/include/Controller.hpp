#pragma once

#include <messages.pb.h>
#include <memory>
#include <Message.hpp>

#include "ISender.hpp"
#include "IUeManager.hpp"


namespace lte
{
namespace enb
{

class Controller{
    
public:
    Controller(std::shared_ptr<IUeManager> ue_manager, std::shared_ptr<ISender> sender)
        :ue_manager_(ue_manager), sender_(sender)
    {}
    
    void handle_attach_req(const AttachReq& attach_req);
    void handle_detach_req(const DetachReq& detach_req);

private:
    std::shared_ptr<IUeManager> ue_manager_;
    std::shared_ptr<ISender> sender_;
};

}
}