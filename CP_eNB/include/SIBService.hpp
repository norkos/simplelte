#pragma once
#include <ITimerWatcher.hpp>

namespace lte
{
namespace enb
{

class ISender;
class IUeManager;

class SIBService : public util::ITimerWatcher{
public:
    SIBService(ISender& sender, const IUeManager& ue_manager):
        sender_(sender), ue_manager_(ue_manager) {}
    
    virtual ~SIBService() = default;
    void notify() override;

private:
    ISender& sender_;
    const IUeManager& ue_manager_;
};
}
}