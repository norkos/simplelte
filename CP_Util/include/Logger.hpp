#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <fstream>

#include "Singleton.hpp"

namespace lte
{
namespace util
{
namespace logger
{

enum class Severity { dbg, error};

class ConsoleLog{
public:
    std::ostream& get_stream(Severity severity_)
    {
        if(severity_ == Severity::dbg) return std::cout;
        else return std::cerr;
    }
};

class FileLog{
public:
    std::ostream& get_stream(Severity severity_)
    {
        return output_stream_;
    }
    
    FileLog(const std::string & file_name = "eNB.log")
    {
        output_stream_.open(file_name, std::ofstream::out | std::ofstream::trunc);
    }
private:
    std::ofstream output_stream_;
};

template<typename LoginPolicy>
class Logger{
public:
    Logger(Severity severity, const char* file_name, int line) : 
        severity_(severity), file_name_(file_name), line_(line), stream_(std::make_unique<std::stringstream>()) 
    {
        *stream_ << "[" << (severity_ == Severity::error ? "ERR" : "DBG") << "] "<< file_name_ << ":" << line_ << " ";
    }
    
    Logger(Logger&& main): severity_(std::move(main.severity_)), file_name_(std::move(main.file_name_)), line_(std::move(main.line_)), stream_(std::move(main.stream_))
    {
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
        LoginPolicy::instance().get_stream(severity_) << stream_->str() << std::endl;
    }
    
private:
    Severity severity_;
    std::string file_name_;
    int line_;
    std::unique_ptr<std::stringstream> stream_;
};

using FilePolicy = Singleton<FileLog>;

inline Logger<FilePolicy> dbg(const char* file_name, int line) // RVO
{
    return Logger<FilePolicy>(Severity::dbg, file_name, line);
}
inline Logger<FilePolicy> err(const char* file_name, int line) // RVOs
{
    return Logger<FilePolicy>(Severity::error, file_name, line);
}

}
}

#define dbg() lte::util::logger::dbg(__FILE__, __LINE__)
#define err() lte::util::logger::err(__FILE__, __LINE__)

}