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
    SIBService(const IUeManager& ue_manager, ISender& sender):
        ue_manager_(ue_manager), sender_(sender) {}
    
    virtual ~SIBService() = default;
    void notify() override;

private:
    const IUeManager& ue_manager_;
    ISender& sender_;
};
}
}