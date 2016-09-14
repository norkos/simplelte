#pragma once
#include <ITimerWatcher.hpp>
#include <Logger.hpp>
namespace lte
{
namespace enb
{

class IServer;
class IUeManager;

class SIBService : public util::ITimerWatcher{
public:
    SIBService(IServer& sender): sender_(sender) {
        dbg() << "SIB";
    }
    
    virtual ~SIBService() = default;
    void notify() override;

private:
    IServer& sender_;
};
}
}