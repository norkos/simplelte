#include "UeManager.hpp"

namespace lte
{
namespace enb
{

void UeManager::add_ue(std::unique_ptr<UeContext> ue)
{
    ues_[ue->id] = std::move(ue);
}

bool UeManager::is_ue(int ue_id) const
{
    return ues_.find(ue_id) != ues_.end();
}

bool UeManager::remove_ue(int ue_id)
{
    auto result = ues_.find(ue_id);
    if(result != ues_.end())
    {
        ues_.erase(result);
        return true;
    }
    return false;
}

UeManager::~UeManager()
{

}
}
}