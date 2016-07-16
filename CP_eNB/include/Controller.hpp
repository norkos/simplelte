#ifndef ENB_CONTROLLER_HPP
#define ENB_CONTROLLER_HPP

#include <messages.pb.h>
#include <unordered_map>
#include "UeContext.hpp"

namespace lte
{
namespace eNB
{

class Controller{
    
public:
    
    void handle_attach_req(const lte::AttachReq& attach_req);
    bool is_ue_attached(int ue_id);

private:
    using UEs = std::unordered_map<int, UeContext>;
    UEs ues;
};

}
}

#endif