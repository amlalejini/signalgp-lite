#pragma once
#ifndef SGPL_OPERATIONS_BINARY_ADD_HPP_INCLUDE
#define SGPL_OPERATIONS_BINARY_ADD_HPP_INCLUDE

#include <map>
#include <string>

#include "../../../../third-party/Empirical/source/tools/string_utils.h"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"

namespace sgpl {

struct Add {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {
    const size_t a = inst.args[0], b = inst.args[1], c = inst.args[2];
    core.registers[a] = core.registers[b] + core.registers[c];
  }

  static std::string name() { return "Add"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    return std::map<std::string, std::string>{
      { "argument a", emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "argument b", emp::to_string( static_cast<int>( inst.args[1] ) ) },
      { "argument c", emp::to_string( static_cast<int>( inst.args[2] ) ) },
      { "summary", "a = b + c" },
    };
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BINARY_ADD_HPP_INCLUDE
