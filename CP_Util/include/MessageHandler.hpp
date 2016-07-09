#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <unordered_map>
#include <typeindex>

template<class MessageBaseT>
class HandlerFunctionBase{
public:
    virtual ~HandlerFunctionBase() {}
    virtual void execute(const MessageBaseT&) = 0;
};

template<class T, class MessageBaseT, class MessageT>
class HandlerFunction : public HandlerFunctionBase<MessageBaseT>{

typedef void(T::*MemFun)(const MessageT&);

public:
        
    HandlerFunction(T* source, MemFun fun): 
        source_(source), function_(fun){ }
    
    virtual ~HandlerFunction() { }
    
    virtual void execute(const MessageBaseT& msg){
        (source_->*function_)(static_cast<const MessageT&>(msg));
    }

private:
    T* source_;
    MemFun function_;
};

template<class MessageBaseT>
class MessageHandler{

typedef std::unordered_map<std::type_index, HandlerFunctionBase<MessageBaseT> *> Handler;
    
public:
    virtual ~MessageHandler(){}
    
    bool handleMessage(const MessageBaseT& msg){
        typename Handler::iterator it = handler_.find(typeid(msg));
        
        if(it != handler_.end()){
            it->second->execute(msg);
            return true;
        }
        return false;
    }
    
    template<class T, class MessageT>
    void registerMessage(T* source, void (T::*memFun)(const MessageT&)){
        handler_[typeid(MessageT)] = new HandlerFunction<T, MessageBaseT, MessageT>(source, memFun);
    }
     
private:
    Handler handler_;
};

#endif