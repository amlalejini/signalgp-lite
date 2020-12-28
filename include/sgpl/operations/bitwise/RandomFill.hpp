#pragma once
#ifndef SGPL_OPERATIONS_BITWISE_RANDOMFILL_HPP_INCLUDE
#define SGPL_OPERATIONS_BITWISE_RANDOMFILL_HPP_INCLUDE

#include <map>
#include <string>

#include "../../../../third-party/Empirical/include/emp/tools/string_utils.hpp"

#include "../../hardware/Core.hpp"
#include "../../program/Instruction.hpp"
#include "../../program/Program.hpp"
#include "../../utility/ThreadLocalRandom.hpp"

namespace sgpl {

struct RandomFill {

  template<typename Spec>
  static void run(
    sgpl::Core<Spec>& core,
    const sgpl::Instruction<Spec>& inst,
    const sgpl::Program<Spec>&,
    typename Spec::peripheral_t&
  ) {

    auto& target = core.registers[ inst.args[0] ];

    sgpl::tlrand.Get().RandFill(
      reinterpret_cast<unsigned char*>( &target ), sizeof( target )
    );

  }

  static std::string name() { return "RandomFill"; }

  static size_t prevalence() { return 1; }

  template<typename Spec>
  static auto descriptors( const sgpl::Instruction<Spec>& inst ) {

    return std::map<std::string, std::string>{
      { "argument a", emp::to_string( static_cast<int>( inst.args[0] ) ) },
      { "summary", "fill a with uniformly-distributed random bits" },
    };
  }

};

} // namespace sgpl

#endif // #ifndef SGPL_OPERATIONS_BITWISE_RANDOMFILL_HPP_INCLUDE
