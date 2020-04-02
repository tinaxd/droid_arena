#include "engine.h"
#include "sprite.h"
#include <SDL.h>
#include <iostream>

namespace da {

Engine::Engine() {}

Engine::~Engine() {}

void Engine::next() {
  if (first) {
    lasttick = SDL_GetTicks();
    first = false;
  }

  auto currtick = SDL_GetTicks();
  auto difftick = currtick - lasttick;

  for (auto &sprite : sprites) {
    Proxy p(this);
    sprite->step(static_cast<float>(difftick) / 1000.0f, p);
  }

  // remove deleted sprite states.

  // update current tick
  lasttick = currtick;
}

void Engine::add_sprite(std::shared_ptr<sprite::State> sprite) {
  sprites.push_back(std::move(sprite));
}

void debug_engine_stdout_(const Engine &engine) {
  std::cout << "current time: " << engine.lasttick << std::endl;
  for (size_t i = 0; i < engine.sprites.size(); i++) {
    auto &sprite = engine.sprites[i];
    std::cout << "[" << i << "] pos: " << sprite->pos()
              << ", vel: " << sprite->vel() << ", rot: " << sprite->rot()
              << std::endl;
  }
}

Proxy::Proxy(Engine *engine) : engine(engine) {}

Proxy::~Proxy() {}

std::vector<const sprite::State *> Proxy::get_other_states() {
  std::vector<const sprite::State *> states;
  for (auto st : engine->sprites) {
    states.push_back(st.get());
  }
  return states;
}

void Proxy::add(sprite::State *state) {
  engine->add_sprite(std::shared_ptr<sprite::State>(state));
}

} // namespace da
