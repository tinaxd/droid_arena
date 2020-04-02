#pragma once

#include "sprite_state.h"
#include "sprite_texture.h"

namespace da {

// Sprite is a combination of a texture and a state.
class Sprite {
public:
  using State = sprite::State;
  using Texture = sprite::Texture;

  Sprite(std::shared_ptr<State> state, std::shared_ptr<Texture> texture = nullptr);

  bool deleted() const;

  const std::shared_ptr<State> &state() const;
  const std::shared_ptr<Texture> &texture() const;

  std::shared_ptr<State> state_mut();
  std::shared_ptr<Texture> texture_mut();

private:
  const std::shared_ptr<State> state_;
  const std::shared_ptr<Texture> texture_;
};

} // namespace da
