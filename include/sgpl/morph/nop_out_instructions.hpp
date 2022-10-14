#pragma once
#ifndef SGPL_MORPH_NOP_OUT_INSTRUCTIONS_HPP_INCLUDE
#define SGPL_MORPH_NOP_OUT_INSTRUCTIONS_HPP_INCLUDE

#include <cassert>
#include <vector>

#include "../program/Program.hpp"

namespace sgpl {

template< typename Spec >
sgpl::Program<Spec> nop_out_instructions(
  sgpl::Program<Spec> program,
  const std::vector< char >& should_nop
) {

  assert( should_nop.size() == program.size() );

  for ( size_t idx{}; idx < program.size(); ++idx ) {
    if ( should_nop[idx] ) program[ idx ].NopOut();
  }

  return program;

}

} // namespace sgpl

#endif // #ifndef SGPL_MORPH_NOP_OUT_INSTRUCTIONS_HPP_INCLUDE
