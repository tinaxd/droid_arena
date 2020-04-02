#include "engine.h"
#include "sprite.h"
#include <SDL.h>
#include <iostream>
#include <queue>

namespace da {

class Proxy : public sprite::QueryProxy {
public:
  explicit Proxy(Engine *engine) {}
  ~Proxy() {}

  virtual std::vector<const sprite::State *> get_other_states() {
    std::vector<const sprite::State *> states;
    for (const auto &st : engine->sprites_) {
      states.push_back(st.get());
    }
    return states;
  }

  virtual void add(sprite::State *state) {
    added.push(std::shared_ptr<sprite::State>(state));
  }

private:
  Engine *engine;
  std::queue<std::shared_ptr<sprite::State>> added;
  
  friend Engine;
};

Engine::Engine() {}

Engine::~Engine() {}

void Engine::next() {
  if (first) {
    lasttick = SDL_GetTicks();
    first = false;
  }

  auto currtick = SDL_GetTicks();
  auto difftick = currtick - lasttick;

  auto p = std::make_unique<Proxy>(this);
  
  for (auto &sprite : sprites_) {
    sprite->step(static_cast<float>(difftick) / 1000.0F, *p);
  }

  // remove deleted sprite states.
  
  // add new sprites in the proxy queue.
  while (!p->added.empty()) {
    add_sprite(std::move(p->added.front()));
    p->added.pop();
  }

  // update current tick
  lasttick = currtick;
}

void Engine::add_sprite(std::shared_ptr<sprite::State> sprite) {
  sprites_.push_back(std::move(sprite));
}

const std::vector<std::shared_ptr<sprite::State>>& Engine::sprites() const {
  return sprites_;
}

void debug_engine_stdout_(const Engine &engine) {
  std::cout << "current time: " << engine.lasttick << std::endl;
  for (size_t i = 0; i < engine.sprites_.size(); i++) {
    auto &sprite = engine.sprites_[i];
    std::cout << "[" << i << "] pos: " << sprite->pos()
              << ", vel: " << sprite->vel() << ", rot: " << sprite->rot()
              << std::endl;
  }
}

} // namespace da
