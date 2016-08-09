#include <gtest/gtest.h>
#include <memory>

#include "UeManager.hpp"

namespace GT = ::testing;

namespace lte
{
namespace enb
{
namespace ut
{

TEST(UeManager, remove_added_ue)
{
    UeManager sut;
    const int id = 1;
    
    auto ue = std::make_unique<UeContext>();
    ue->id = id;
    
    sut.add_ue(std::move(ue));
    
    ASSERT_TRUE(sut.remove_ue(id));
}

TEST(UeManager, is_ue)
{
    UeManager sut;
    const int id = 1;
    
    auto ue = std::make_unique<UeContext>();
    ue->id = id;
    
    sut.add_ue(std::move(ue));
    
    ASSERT_TRUE(sut.is_ue(id));
}

TEST(UeManager, no_ue)
{
    UeManager sut;
    const int id = 1;
    
    ASSERT_FALSE(sut.is_ue(id));
}

TEST(UeManager, remove_not_existing_ue)
{
    UeManager sut;
    const int id = 1;
    
    ASSERT_FALSE(sut.remove_ue(id));
}

}
}
}