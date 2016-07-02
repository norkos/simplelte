#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

#include <unordered_map>
#include <typeindex>

#include "HandlerFunction.hpp"

template<class MessageBaseT>
class MessageHandler{

typedef std::unordered_map<std::type_index, HandlerFunctionBase<MessageBaseT> *> Handler;
    
public:
    ~MessageHandler(){}
    
    void handleMessage(const MessageBaseT& msg){
        typename Handler::iterator it = handlers.find(typeid(msg));
        if(it != handlers.end()){
            it->second->execute(msg);
        }
    }
    
    template<class T, class MessageT>
    void registerMessage(T* source, void (T::*memFun)(const MessageT&)){
        handlers[typeid(MessageT)] = new HandlerFunction<T, MessageT, MessageBaseT>(source, memFun);
    }
     
private:
    Handler handlers;
};

#endif