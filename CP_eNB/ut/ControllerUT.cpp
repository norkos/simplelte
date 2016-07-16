#include <gtest/gtest.h>
#include <memory>

#include "Controller.hpp"

namespace GT = ::testing;

namespace lte
{
namespace eNB
{
namespace ut
{
    
TEST(ControllerTest, message_was_not_handled)
{
    Controller sut;
    lte::AttachReq attach_req;
    int ue_id = 10;
    attach_req.set_id(ue_id);
    
    sut.handle_attach_req(attach_req);
    
    ASSERT_TRUE(sut.is_ue_attached(ue_id));
}

}
}
}