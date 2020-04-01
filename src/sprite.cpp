#include "sprite.h"
#include "sprite_instruction.h"
#include "sprite_state.h"
#include "sprite_texture.h"
#include <SDL.h>

namespace da::sprite {

State::State(Position init_pos, Velocity init_vel, Rotation init_rot)
    : pos_(init_pos), vel_(init_vel), rot_(init_rot) {}

const Position &State::pos() const { return pos_; }

const Velocity &State::vel() const { return vel_; }

const Rotation &State::rot() const { return rot_; }

Position &State::pos_mut() { return pos_; }

Velocity &State::vel_mut() { return vel_; }

Rotation &State::rot_mut() { return rot_; }

const HP &State::hp() const { return hp_; }

bool State::immortal() const { return std::get_if<int>(&hp_) == nullptr; }

void State::step(float deltatime, QueryProxy &) {
  pos_ += vel_ * (double)deltatime;
}

SMState::SMState(Position init_pos, Velocity init_vel, Rotation init_rot,
                 InstructionSet instset)
    : State(init_pos, init_vel, init_rot), instset(instset) {}

SMState::~SMState() {}

void SMState::step(float deltatime, QueryProxy &p) {
  State::step(deltatime, p);

  switch (inst) {
  case Instruction::TE:
    // check if at least one enemy is in front of me.
    handle_rotate_to_enemy();
    break;
  case Instruction::ShootGatling:
  case Instruction::ShootGun:
  case Instruction::ShootLaser:
    // use weapon.
    handle_shoot(inst);
    break;
  default:
    // move
    handle_move(inst);
    break;
  }
}

void SMState::handle_move(Instruction direction) {
  switch (direction) {
    
  }
}

Texture::Texture(SDL_Texture *t) : t_(t) {}

Texture::~Texture() { SDL_DestroyTexture(t_); }

} // namespace da::sprite

namespace da {

Sprite::Sprite(std::shared_ptr<State> state, std::shared_ptr<Texture> texture)
    : state(state), texture(texture) {}

} // namespace da
