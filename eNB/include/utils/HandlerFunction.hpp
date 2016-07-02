#ifndef HANDLER_FUNCTION
#define HANDLER_FUNCTION

#include "HandlerFunctionBase.hpp"

template<class T, class MessageT, class MessageBaseT>
class HandlerFunction : public HandlerFunctionBase<MessageBaseT>{

    typedef void(T::*MemFun)(const MessageT&);

public:
        
    HandlerFunction(T* source, MemFun fun): obj(source), memFun(fun){ 
    }
    
    virtual ~HandlerFunction() {}
    
    virtual void execute(const MessageBaseT& msg){
        (obj->*memFun)(static_cast<const MessageT&>(msg));
    }

private:
    T* obj;
    MemFun memFun;
};
    

#endif