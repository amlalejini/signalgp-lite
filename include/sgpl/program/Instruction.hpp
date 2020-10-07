#pragma once

#include <algorithm>
#include <cstddef>

#include "../../../third-party/Empirical/source/base/array.h"
#include "../../../third-party/Empirical/source/tools/BitSet.h"
#include "../../../third-party/Empirical/source/tools/Random.h"

namespace sgpl {

template<typename Library>
struct Instruction {

  unsigned char op_code;

  emp::array<unsigned char, 3> args;

  emp::BitSet<32> tag;

  Instruction() = default;

  Instruction(emp::Random& rand)
  : op_code( rand.GetUInt( Library::GetSize() ) )
  , tag( rand )
  {
    std::generate(
      std::begin( args ),
      std::end( args ),
      [&rand](){ return rand.GetUInt( 5 ); }
    );
    emp_assert( Library::GetSize() < 256 );
  }

};

} // namespace sgpl
