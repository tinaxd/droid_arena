#include "sprite_instruction.h"

namespace da {

InstructionSet::InstructionSet() {}

InstructionSet::InstructionSet(std::vector<Instruction> instructions,
                               std::unique_ptr<SpecialInstruction> special)
    : instructions_(std::move(instructions)), special(std::move(special)) {}

InstructionSet::InstructionSet(const InstructionSet &s)
    : instructions_(s.instructions()),
      special(std::unique_ptr<SpecialInstruction>(&*s.special.get())) {}

InstructionSet::InstructionSet(std::initializer_list<Instruction> il) {
  static_assert(il.size() <= MAX_INSTRUCTIONS, "over MAX_INSTRUCTIONS");
  InstructionSet(std::vector<Instruction>(il), nullptr);
}

bool InstructionSet::has_special_instruction() { return special != nullptr; }

void InstructionSet::add_special_instruction(
    std::unique_ptr<SpecialInstruction> special) {
  this->special = special;
}

void InstructionSet::delete_special_instruction() { special = nullptr; }

size_t InstructionSet::instructions_count() { return instructions.size(); }

std::vector<Instruction>& instructions_mut() { return instructions_; }

const std::vector<Instruction>& instructions() const { return instructions_; }

} // namespace da
