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
    virtual ~UeManager() = default;
    void add_ue(std::unique_ptr<UeContext> ue) override;
    bool remove_ue(int ue_id) override;
    bool is_ue(int ue_id) const override;

private:
    UEs ues_;
};
}
}
