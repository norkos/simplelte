#ifndef ENB_CONTROLLER_HPP
#define ENB_CONTROLLER_HPP

#include <messages.pb.h>

namespace lte
{
namespace eNB
{
namespace server
{

class Controller{
    
public:
    Controller(){}
    virtual ~Controller(){}
    
    void handle_attach_req(const lte::AttachReq& attach_req);
};
}
}
}

#endif