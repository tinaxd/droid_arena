#pragma once

#include "sprite_state.h"
#include <memory>
#include <vector>

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
  
  const std::vector<std::shared_ptr<sprite::State>>& sprites() const;

private:
  std::vector<std::shared_ptr<sprite::State>> sprites_;

  uint32_t lasttick = 0;

  mutable bool first = true;

  friend Proxy;
  friend void debug_engine_stdout_(const Engine &engine);
};

void debug_engine_stdout_(const Engine &engine);

} // namespace da
