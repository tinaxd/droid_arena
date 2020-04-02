#pragma once

#include "sprite_instruction.h"
#include "util.h"
#include <optional>
#include <tuple>
#include <variant>

namespace da::sprite {

using Position = da::Vector2D<double>;
using Velocity = da::Vector2D<double>;
using Rotation = double;
using HP = std::variant<int, std::monostate>;

class State;
class SMState;
class QueryProxy;

class State {
public:
  State(Position init_pos, Velocity init_vel = Vector2D<double>(),
        Rotation init_rot = 0.0);
  virtual ~State();

  const Position &pos() const;
  const Velocity &vel() const;
  const Rotation &rot() const;
  const Rotation &ang_vel() const;

  Position &pos_mut();
  Velocity &vel_mut();
  Rotation &rot_mut();
  Rotation &ang_vel_mut();

  bool immortal() const;
  const HP &hp() const;

  virtual void step(float deltatime, QueryProxy &p);

  bool deleted() const;
  void mark_delete();

  double speed() const;
  double ang_speed() const;
  double radius() const;
  
  int team() const;
  void set_team(int team);

private:
  Position pos_;
  Velocity vel_;
  Rotation rot_;
  Rotation ang_vel_;
  HP hp_;
  bool deleted_ = false;
  double speed_ = 100.0;
  double ang_speed_ = M_PI / 6.0;
  double radius_ = 30.0;
  int team_ = 0;
};

/// State-Machine State extension.
class SMState : public State {
public:
  SMState(Position init_pos, Velocity init_vel, Rotation init_rot,
          InstructionSet instset);
  virtual ~SMState();

  virtual void step(float deltatime, QueryProxy &p) override;

private:
  InstructionSet instset;
  /// The index of the currently selected instruction.
  ssize_t inst_ptr = 0;
  /// Increment instruction pointer.
  void incr_inst_ptr();
  /// The currently selected instruction.
  Instruction inst;
  void set_current_inst();
  /// Elapsed time since the current instruction started.
  float inst_time = 0.0f;
  /// If inst_time reaches this time, increment instruction pointer.
  std::optional<float> inst_limit_time;
  void update_inst_limit_time();

  void handle_move(Instruction direction);
  void handle_shoot(Instruction gun_type, QueryProxy &p);
  void handle_rotate_to_enemy(QueryProxy &p);
  
  void accumulate_deltatime(float deltatime);
};

class QueryProxy {
public:
  virtual ~QueryProxy() {}
  virtual std::vector<const State *> get_other_states() = 0;
  virtual void add(State *state) = 0;
};

} // namespace da::sprite
