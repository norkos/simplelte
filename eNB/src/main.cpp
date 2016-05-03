#include <messages.pb.h>
#include <zmq.hpp>
#include <string>
#include <iostream>

int response(lte::AttachReq& req)
{
    return req.id() * 2;
}