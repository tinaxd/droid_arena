#include "sprite.h"
#include "sprite_instruction.h"
#include "sprite_state.h"
#include "sprite_texture.h"
#include <SDL.h>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>

namespace da::sprite {

State::State(Position init_pos, Velocity init_vel, Rotation init_rot)
    : pos_(init_pos), vel_(init_vel), rot_(init_rot) {}

State::~State() {}

const Position &State::pos() const { return pos_; }

const Velocity &State::vel() const { return vel_; }

const Rotation &State::rot() const { return rot_; }

const Rotation &State::ang_vel() const { return ang_vel_; }

Position &State::pos_mut() { return pos_; }

Velocity &State::vel_mut() { return vel_; }

Rotation &State::rot_mut() { return rot_; }

Rotation &State::ang_vel_mut() { return ang_vel_; }

const HP &State::hp() const { return hp_; }

bool State::immortal() const { return std::get_if<int>(&hp_) == nullptr; }

void State::step(float deltatime, QueryProxy & /*unused*/) {
  pos_ += vel_ * (double)deltatime;
}

bool State::deleted() const { return deleted_; }

void State::mark_delete() { deleted_ = true; }

double State::speed() const { return speed_; }

double State::ang_speed() const { return ang_speed_; }

double State::radius() const { return radius_; }

SMState::SMState(Position init_pos, Velocity init_vel, Rotation init_rot,
                 const InstructionSet &instset)
    : State(init_pos, init_vel, init_rot), instset(instset) {
  assert(instset.instructions_count() != 0);
}

SMState::~SMState() {}

void SMState::incr_inst_ptr() {
  inst_ptr++;
  if (inst_ptr >= instset.instructions_count()) {
    inst_ptr = 0;
  }
  inst_time = 0.0;
}

void SMState::set_current_inst() {
  if (inst_limit_time) {
    if (inst_time > inst_limit_time.value()) {
      incr_inst_ptr();
    }
  }

  inst = instset.at(inst_ptr);
  update_inst_limit_time();
}

void SMState::update_inst_limit_time() {
  switch (inst) {
  case Instruction::TE:
    inst_limit_time = std::optional<float>();
    break;
  case Instruction::ShootGatling:
  case Instruction::ShootGun:
  case Instruction::ShootLaser:
    inst_limit_time = std::optional<float>(0.5);
  default:
    inst_limit_time = std::optional<float>(1.0);
  }
}

void SMState::step(float deltatime, QueryProxy &p) {
  accumulate_deltatime(deltatime);
  set_current_inst();

  switch (inst) {
  case Instruction::TE:
    // check if at least one enemy is in front of me.
    handle_rotate_to_enemy(p);
    break;
  case Instruction::ShootGatling:
  case Instruction::ShootGun:
  case Instruction::ShootLaser:
    // use weapon.
    handle_shoot(inst, p);
    break;
  default:
    // move
    handle_move(inst);
    break;
  }

  State::step(deltatime, p);
}

void SMState::handle_move(Instruction direction) {
  int fb = 0;
  int side = 0;
  switch (direction) {
  case Instruction::F:
    fb++;
    break;
  case Instruction::B:
    fb--;
    break;
  case Instruction::FL:
    fb++;
    side++;
    break;
  case Instruction::FR:
    fb++;
    side--;
    break;
  case Instruction::BL:
    fb--;
    side++;
    break;
  case Instruction::BR:
    fb--;
    side--;
    break;
  case Instruction::L:
    side++;
    break;
  case Instruction::R:
    side--;
    break;
  default:
    throw std::logic_error("handle_move unreachable");
  }

  const auto f = fb * speed();
  const auto s = side * speed();
  const auto x = f * sin(rot()) + s * cos(rot());
  const auto y = f * cos(rot()) - s * sin(rot());
  vel_mut() = Vector2D(x, y);
}

void SMState::handle_shoot(Instruction gun_type, QueryProxy &p) {
  // instantiate gun
  // QueryProxy.add(gun)
  // TODO: make gun variations
  const auto shot_speed = 200.0;
  const Vector2D my_dir(1.0 * sin(rot()) + 1.0 * cos(rot()),
                        1.0 * cos(rot()) - 1.0 * sin(rot()));
  auto *shot = new State(pos(), my_dir * shot_speed);
  p.add(shot);
}

void SMState::handle_rotate_to_enemy(QueryProxy &p) {
  const auto &others = p.get_other_states();
  constexpr Rotation MAX_ERROR = M_PI * (5.0 / 180.0);

  const auto curr_rot = rot();
  const auto curr_pos = pos();
  if (std::any_of(
          others.cbegin(), others.cend(), [curr_rot, curr_pos](auto other) {
            const Vector2D my_dir(1.0 * sin(curr_rot) + 1.0 * cos(curr_rot),
                                  1.0 * cos(curr_rot) - 1.0 * sin(curr_rot));
            const auto o_dir = other->pos() - curr_pos;
            const auto rot_diff = da::Vector2D<double>::rot(my_dir, o_dir);
            return rot_diff < MAX_ERROR;
          })) {
    // stop rotation.
    ang_vel_mut() = 0.0;
  } else {
    // rotate until found an enemy.
    // TODO: in which direction to rotate?
    ang_vel_mut() = ang_speed();
  }
}

void SMState::accumulate_deltatime(float deltatime) { inst_time += deltatime; }

Texture::Texture(SDL_Texture *t) : t_(t) {}

Texture::~Texture() { SDL_DestroyTexture(t_); }

} // namespace da::sprite

namespace da {

Sprite::Sprite(std::shared_ptr<State> state, std::shared_ptr<Texture> texture)
    : state_(std::move(state)), texture_(std::move(texture)) {}

const std::shared_ptr<Sprite::State> &Sprite::state() const { return state_; }

const std::shared_ptr<Sprite::Texture> &Sprite::texture() const {
  return texture_;
}

std::shared_ptr<Sprite::State> Sprite::state_mut() { return state_; }

std::shared_ptr<Sprite::Texture> Sprite::texture_mut() { return texture_; }

} // namespace da
