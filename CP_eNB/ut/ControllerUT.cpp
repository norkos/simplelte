#include <gtest/gtest.h>
#include <memory>

#include "Controller.hpp"
#include "MockUeManager.hpp"

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
    //  given
    auto ue_manager = std::make_shared<GT::StrictMock<MockUeManager>>();            
    auto sut = Controller(ue_manager);
    auto message = AttachReq();
    message.set_id(10);
    
    //  expect
    EXPECT_CALL(*ue_manager, add_ue_proxy(is_ue_id_eq(message.id())));
    
    //  when
    sut.handle_attach_req(message);
}

TEST(ControllerTest, detach_ue)
{
    //  given
    auto ue_manager = std::make_shared<GT::StrictMock<MockUeManager>>();            
    auto sut = Controller(ue_manager);
    auto message = DetachReq();
    message.set_id(10);
    
    //  expect
    EXPECT_CALL(*ue_manager, remove_ue(message.id()));
    
    //  when
    sut.handle_detach_req(message);
}

}
}
}