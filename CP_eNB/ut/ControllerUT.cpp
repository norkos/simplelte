#include <gtest/gtest.h>
#include <memory>

#include "Controller.hpp"
#include "MockUeManager.hpp"
#include "MockTimer.hpp"
#include "MockServer.hpp"
#include "UeContext.hpp"

namespace GT = ::testing;

namespace lte
{
namespace enb
{
namespace ut
{

MATCHER_P(is_ue_id_eq, n, "") { return arg->id == n; }

TEST(ControllerTest, attach_ue)
{
    /**
    //  given
    auto ue_manager = std::make_shared<GT::StrictMock<MockUeManager>>();            
    auto sender = std::make_shared<GT::StrictMock<MockServer>>();
    Controller sut(*ue_manager, *sender );
    rrc::AttachReq message;
    
    message.set_id(10);
    
    //  expect
    EXPECT_CALL(*ue_manager, is_ue(message.id())).WillOnce(GT::Return(false));
    EXPECT_CALL(*ue_manager, add_ue_proxy(is_ue_id_eq(message.id())));
    EXPECT_CALL(*sender, send_proxy(GT::_));
    
    //  when
    sut.handle_attach_req(message);
    */
    google::protobuf::ShutdownProtobufLibrary();
    
}

}
}
}