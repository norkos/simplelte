#pragma once

#include <memory>

namespace lte
{
namespace enb
{
    
struct UeContext;

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

