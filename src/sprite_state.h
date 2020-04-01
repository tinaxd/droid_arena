#pragma once

#include <tuple>
#include <variant>
#include "util.h"
#include "sprite_instruction.h"

namespace da::sprite
{
    
using Position = da::Vector2D<double>;
using Velocity = da::Vector2D<double>;
using Rotation = double;
using HP = std::variant<int, std::monostate>;

class State;
class SMState;
class QueryProxy;

class State
{
public:
    State(Position init_pos, Velocity init_vel, Rotation init_rot);
    virtual ~State();
    
    const Position& pos() const;
    const Velocity& vel() const;
    const Rotation& rot() const;
    
    Position& pos_mut();
    Velocity& vel_mut();
    Rotation& rot_mut();
    
    bool immortal() const;
    const HP& hp() const;
    
    virtual void step(float deltatime, QueryProxy& p);
    
    bool deleted() const;
    void mark_delete();
    
private:
    Position pos_;
    Velocity vel_;
    Rotation rot_;
    HP hp_;
    bool deleted_;
};

/// State-Machine State extension.
class SMState : public State
{
public:
    SMState(Position init_pos, Velocity init_vel, Rotation init_rot, InstructionSet instset);
    virtual ~SMState();
    
    virtual void step(float deltatime, QueryProxy& p) override;
    
private:
    InstructionSet instset;
    /// the index of the currently selected instruction.
    ssize_t inst_ptr = 0;
    /// the currently selected instruction.
    Instruction inst;
    /// elapsed time since the current instruction started.
    float inst_time = 0.0f;
    
    void handle_move(Instruction direction);
    void handle_shoot(Instruction gun_type);
    void handle_rotate_to_enemy();
};

class QueryProxy
{
public:
    virtual ~QueryProxy() {}
    virtual std::vector<const State&> get_other_states() = 0;
};
    
}
