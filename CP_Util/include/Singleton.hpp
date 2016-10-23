#pragma once
namespace lte
{
namespace util
{

template<class T> class Singleton
{
public:
    static T& instance()
    {
        static T inst;
        return inst;
    }
    
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;
private:
    Singleton() {}
};
}
}