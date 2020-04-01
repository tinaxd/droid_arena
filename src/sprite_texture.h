#pragma once

#include <SDL.h>
#include <memory>

namespace da::sprite
{
    
class Texture
{
public:
    explicit Texture(SDL_Texture *t);
    ~Texture();
    
private:
    SDL_Texture *t_;
};
    
}
