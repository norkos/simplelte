#ifndef HANDLER_FUNCTION_BASE
#define HANDLER_FUNCTION_BASE

template<class MessageBaseT>
class HandlerFunctionBase{
public:
    virtual ~HandlerFunctionBase() {}
    virtual void execute(const MessageBaseT&) = 0;
};
    

#endif