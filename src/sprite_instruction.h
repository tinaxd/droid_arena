#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

namespace da::sprite {

class InstructionSet;
struct SpecialInstruction;
struct Condition;

enum class Instruction {
  F,
  B,
  FR,
  FL,
  BR,
  BL,
  R,
  L,
  TE, // To the Enemy
  ShootGun,
  ShootLaser,
  ShootGatling,
};

enum class ConditionType {
  DistanceGT,
  DistanceLT,
};

class InstructionSet {
public:
  InstructionSet();
  InstructionSet(std::vector<Instruction> instructions,
                 std::unique_ptr<SpecialInstruction> special = nullptr);
  InstructionSet(const InstructionSet &s);
  InstructionSet(std::initializer_list<Instruction> il);

  InstructionSet &operator=(const InstructionSet &s);

  bool has_special_instruction() const;
  void add_special_instruction(std::unique_ptr<SpecialInstruction> special);
  void delete_special_instruction();
  size_t instructions_count() const;

  Instruction at(size_t index) const;

  std::vector<Instruction> &instructions_mut();
  const std::vector<Instruction> &instructions() const;

  constexpr static size_t MAX_INSTRUCTIONS = 10;

private:
  std::vector<Instruction> instructions_;
  std::unique_ptr<SpecialInstruction> special = nullptr;
};

struct Condition {
  ConditionType type;
  int arg;
};

struct SpecialInstruction {
public:
  SpecialInstruction(Condition cond, Instruction inst);

  Condition cond;
  Instruction inst;
};

} // namespace da::sprite
