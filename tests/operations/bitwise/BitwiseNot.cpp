#include "Catch/single_include/catch2/catch.hpp"
#include "conduit/include/uitsl/polyfill/bit_cast.hpp"

#include "sgpl/algorithm/execute_core.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/bitwise/BitwiseNot.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::BitwiseNot>;
struct spec_t : public sgpl::Spec<library_t> {
  static constexpr inline size_t num_registers{ 4 };
};

TEST_CASE("Test BitwiseNot") {

  sgpl::Program<spec_t> program{1};

  sgpl::Core<spec_t> core;

  // set up initial state
  const float val1 = std::bit_cast<float>(0b00000000000000000000000001001001);
  const float val2 = std::bit_cast<float>(0b11111111111111111111111110110110);

  // set up values to operate on in register
  core.registers[0] = val1;

  // set up what registers to operate on
  program[0].args[0] = 1;
  program[0].args[1] = 0;

  // check initial state
  REQUIRE(core.registers == emp::array<float, 8>{val1, 0, 0, 0, 0, 0, 0, 0});

  // execute single instruction
  sgpl::advance_core(core, program);

  std::cout << std::bitset<8>(core.registers[1]) << std::endl;

  // check final state
  REQUIRE(core.registers == emp::array<float, 4>{operand1, result, {}, {}});
}
