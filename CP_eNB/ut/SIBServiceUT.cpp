#include <gtest/gtest.h>
#include <memory>

#include "SIBService.hpp"
#include "MockSender.hpp"
#include "MockUeManager.hpp"

namespace GT = ::testing;

namespace lte
{
namespace enb
{
namespace ut
{

TEST(SIBService, notify_ues)
{
    //  given     
    auto sender = std::make_shared<GT::StrictMock<MockSender>>();
    SIBService sut(*sender);
    
    //  expected
    EXPECT_CALL(*sender, send_proxy(GT::_));
    
    //  when
    sut.notify();
}

}
}
}