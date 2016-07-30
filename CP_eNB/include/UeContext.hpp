#pragma once

namespace lte
{
namespace enb
{

struct UeContext
{
    int id;
    
    int get_id() const { return id; } 
};

}
}