#include "engine.h"
#include "sprite.h"
#include <SDL.h>

namespace da {

Engine::Engine() {}

Engine::~Engine() {}

void Engine::start() {
  auto currtick = SDL_GetTicks();
  auto difftick = lasttick - currtick;

  for (auto &sprite : sprites) {
    sprite->step(static_cast<float>(difftick) / 1000.0f);
  }

  // remove deleted sprite states.
}

void Engine::add_sprite(std::shared_ptr<sprite::State> sprite) {
  sprites.push_back(std::move(sprite));
}

} // namespace da
