#pragma once
#include <memory>
#include <sstream>
#include <iostream>

namespace lte
{
namespace util
{
    
enum class Severity { dbg, error};

class Logger{
public:
    Logger(Severity severity) : 
        severity_(severity), stream_(std::make_unique<std::stringstream>()) {
    }
    
    Logger(Logger&& main): severity_(std::move(main.severity_)),stream_(std::move(main.stream_))
    {
    }
    
    std::ostream& get_stream()
    {
        if(severity_ == Severity::dbg) return std::cout;
        else return std::cerr;
    }
    
    template<typename T>
    Logger& operator<<(const T& value)
    {
        *stream_ << value;
        return *this;
    }
    
    ~Logger() 
    {
        if(stream_ == nullptr) return;
        get_stream() << stream_->str() << std::endl;
    }
    
private:
    Severity severity_;
    std::unique_ptr<std::stringstream> stream_;
};

}

inline util::Logger dbg() // RVO
{
    return util::Logger(util::Severity::dbg);
}
inline util::Logger err() // RVOs
{
    return util::Logger(util::Severity::error);
}
}