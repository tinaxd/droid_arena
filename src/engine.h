#pragma once

#include <memory>
#include <vector>
#include "sprite_state.h"

namespace da {

class Engine;
class Proxy;

/// Game engine which manages sprite-states.
///
/// Assuming SDL_Init is already called.
class Engine {
public:
  Engine();
  ~Engine();

  void next();

  void add_sprite(std::shared_ptr<sprite::State> sprite);

private:
  std::vector<std::shared_ptr<sprite::State>> sprites;

  uint32_t lasttick = 0;
  
  mutable bool first = true;
  
  friend Proxy;
  friend void debug_engine_stdout_(const Engine& engine);
};

void debug_engine_stdout_(const Engine& engine);

class Proxy : public sprite::QueryProxy {
public:
  explicit Proxy(Engine *engine);
  ~Proxy();
  
  virtual std::vector<const sprite::State *> get_other_states();
  virtual void add(sprite::State *state);
  
private:
  Engine *engine;
};

} // namespace da
