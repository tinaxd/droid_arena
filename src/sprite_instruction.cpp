#include "sprite_instruction.h"
#include <cassert>

namespace da::sprite {

InstructionSet::InstructionSet() {}

InstructionSet::InstructionSet(std::vector<Instruction> instructions,
                               std::unique_ptr<SpecialInstruction> special)
    : instructions_(std::move(instructions)), special(std::move(special)) {}

InstructionSet::InstructionSet(const InstructionSet &s)
    : instructions_(s.instructions()),
      special(std::unique_ptr<SpecialInstruction>(&*s.special.get())) {}

InstructionSet::InstructionSet(std::initializer_list<Instruction> il)
    : InstructionSet(std::vector<Instruction>(il.begin(), il.end()), nullptr) {
  // FIXME: static assert il.size()
  assert(il.size() <= MAX_INSTRUCTIONS);
}

bool InstructionSet::has_special_instruction() const {
  return special != nullptr;
}

void InstructionSet::add_special_instruction(
    std::unique_ptr<SpecialInstruction> special) {
  this->special = std::move(special);
}

void InstructionSet::delete_special_instruction() { special = nullptr; }

size_t InstructionSet::instructions_count() const {
  return instructions_.size();
}

Instruction InstructionSet::at(size_t index) const {
  return instructions_.at(index);
}

std::vector<Instruction> &InstructionSet::instructions_mut() {
  return instructions_;
}

const std::vector<Instruction> &InstructionSet::instructions() const {
  return instructions_;
}

} // namespace da::sprite
