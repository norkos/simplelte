#pragma once

#include <messages.pb.h>
#include <memory>

#include "IUeManager.hpp"

namespace lte
{
namespace enb
{

class Controller{
    
public:
    Controller(std::shared_ptr<IUeManager> ue_manager):ue_manager_(ue_manager)
    {}
    
    void handle_attach_req(const AttachReq& attach_req);
    void handle_detach_req(const DetachReq& detach_req);

private:
    std::shared_ptr<IUeManager> ue_manager_;
};

}
}