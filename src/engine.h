#pragma once

#include <vector>
#include <memory>

namespace da
{
    
namespace sprite
{
    class State;
}
 
class Engine
{
public:
    Engine();
    ~Engine();
    
    void start();
    
    void add_sprite(std::shared_ptr<sprite::State> sprite);
    
private:
    std::vector<std::shared_ptr<sprite::State>> sprites;
    
    uint32_t lasttick = 0;
    
};
    
}
