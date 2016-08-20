#pragma once

#include <google/protobuf/message.h>
#include <ostream>

namespace lte
{
namespace util
{
    
typedef google::protobuf::Message Message;

inline std::ostream& operator<<(std::ostream& stream, const Message& message)
{
    stream << "Message " << message.GetTypeName() << ": " << message.DebugString();
    return stream;
}

}
}