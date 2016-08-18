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
    SIBService(ISender& sender): sender_(sender) {}
    
    virtual ~SIBService() = default;
    void notify() override;

private:
    ISender& sender_;
};
}
}