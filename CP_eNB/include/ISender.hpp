#pragma once

template<class T>
class ISender{
public:
    virtual ~ISender(){}
    virtual void send(const T&) = 0;
};