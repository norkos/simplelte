#pragma once

#include <unordered_map>
#include "IUeManager.hpp"
#include "UeContext.hpp"

namespace lte
{
namespace enb
{

class UeManager : public IUeManager
{

using UEs = std::unordered_map<int, std::unique_ptr<UeContext>>;
    
public:
    virtual ~UeManager();
    virtual void add_ue(std::unique_ptr<UeContext> ue);
    virtual bool remove_ue(int ue_id);
    virtual bool is_ue(int ue_id) const;

private:
    UEs ues_;
};
}
}
