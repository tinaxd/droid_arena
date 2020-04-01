#pragma once

#include "sprite_state.h"
#include "sprite_texture.h"

namespace da
{
 
// Sprite is a combination of a texture and a state.
class Sprite
{
public:
    using State = sprite::State;
    using Texture = sprite::Texture;
    
    Sprite(std::shared_ptr<State> state, std::shared_ptr<Texture> texture);
    
    bool deleted() const;
    
private:
    std::shared_ptr<State> state;
    std::shared_ptr<Texture> texture;
};
    
}
