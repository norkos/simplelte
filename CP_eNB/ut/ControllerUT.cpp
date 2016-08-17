#include <gtest/gtest.h>
#include <memory>

#include "Controller.hpp"
#include "MockUeManager.hpp"
#include "MockTimer.hpp"
#include "MockSender.hpp"
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
    //  given
    auto ue_manager = std::make_shared<GT::StrictMock<MockUeManager>>();            
    auto sender = std::make_shared<GT::StrictMock<MockSender>>();
    Controller sut(*ue_manager, *sender);
    rrc::AttachReq message;
    
    message.set_id(10);
    
    //  expect
    EXPECT_CALL(*ue_manager, is_ue(message.id())).WillOnce(GT::Return(false));
    EXPECT_CALL(*ue_manager, add_ue_proxy(is_ue_id_eq(message.id())));
    EXPECT_CALL(*sender, send_proxy(GT::_));
    
    //  when
    sut.handle_attach_req(message);
}

TEST(ControllerTest, attach_already_attached_ue)
{
    //  given
    auto ue_manager = std::make_shared<GT::StrictMock<MockUeManager>>();            
    auto sender = std::make_shared<GT::StrictMock<MockSender>>();
    Controller sut(*ue_manager, *sender);
    rrc::AttachReq message;
    
    message.set_id(10);
    
    //  expect
    EXPECT_CALL(*ue_manager, is_ue(message.id())).WillOnce(GT::Return(true));
    EXPECT_CALL(*sender, send_proxy(GT::_));
    
    //  when
    sut.handle_attach_req(message);
}

TEST(ControllerTest, detach_ue)
{
    //  given
    auto ue_manager = std::make_shared<GT::StrictMock<MockUeManager>>();            
    auto sender = std::make_shared<GT::StrictMock<MockSender>>();
    Controller sut(*ue_manager, *sender);
    rrc::DetachReq message;
    message.set_id(10);
    
    //  expect
    EXPECT_CALL(*ue_manager, remove_ue(message.id()));
    EXPECT_CALL(*sender, send_proxy(GT::_));
    
    //  when
    sut.handle_detach_req(message);
}


class ControllerTimerStub : public Controller
{
public:
    using Controller::Controller;
    void set_timer(util::ITimer* timer)
    {        
        timer_.reset(timer);
    }
};

TEST(TimerTest, is_timer_invoked)
{
    //  given
    auto ue_manager = std::make_shared<GT::StrictMock<MockUeManager>>();            
    auto sender = std::make_shared<GT::StrictMock<MockSender>>();
    ControllerTimerStub sut(*ue_manager, *sender);
    
    auto timer = new GT::StrictMock<MockTimer>();
    sut.set_timer(timer);
    
    //  expect
    EXPECT_CALL(*timer, update());
    
    //  when
    sut.handle_timer_ind(internal::TimerInd());
}

}
}
}