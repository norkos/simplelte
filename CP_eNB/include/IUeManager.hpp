#pragma once

#include <memory>

#include "UeContext.hpp"

namespace lte
{
namespace enb
{
class IUeManager
{
public:
    virtual ~IUeManager() {}
    virtual void add_ue(std::unique_ptr<UeContext> ue) = 0;
    virtual bool remove_ue(int ue_id) = 0;
    virtual bool is_ue(int ue_id) const = 0;
};
}
}

