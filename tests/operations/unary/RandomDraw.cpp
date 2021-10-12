#include "Catch/single_include/catch2/catch.hpp"
#include "Empirical/include/emp/data/DataNode.hpp"

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/hardware/Core.hpp"
#include "sgpl/library/OpLibrary.hpp"
#include "sgpl/operations/unary/RandomDraw.hpp"
#include "sgpl/program/Program.hpp"
#include "sgpl/spec/Spec.hpp"
#include "sgpl/utility/ThreadLocalRandom.hpp"

// typedefs
using library_t = sgpl::OpLibrary<sgpl::RandomDraw>;
using spec_t = sgpl::Spec<library_t>;

/**
 * This testcase is intended to check the behavior of RandomDraw.
 * One hundred random RandomDraw operations are executed one hundred times each.
 * The total sums of each replicate are tallied, and the test only passes if the overall
 * standard deviation is sufficiently large (>1,000), the smallest sum is smaller than 10,
 * and the largest sum is greater than 100,000.
 */
TEST_CASE("Test RandomDraw") {
  // define number of replicates
  constexpr size_t replicates = 100;

  // initialize tlrand
  sgpl::tlrand.Reseed(1);

  emp::DataNode<size_t, emp::data::Current, emp::data::Range, emp::data::Stats> data;

  for (size_t i{}; i < replicates; i++) {
    // create and initialize cpu
    sgpl::Cpu<spec_t> cpu;
    for (size_t i{}; i < 20; ++i) cpu.TryLaunchCore();

    // make a program of length 1
    sgpl::Program<spec_t> program{1};
    // tell instruction to operate on 0th register
    program[0].args[0] = 0;

    size_t replicate_count{};
    for (size_t j{}; j < 100; j++) {
      // execute instruction
      sgpl::execute_cpu(1, cpu, program);
      // store result (either true or false!)
      replicate_count += cpu.GetActiveCore().registers[0];
    }

    data.Add(replicate_count);
  }

  // check that standard deviation is sufficiently large
  // and that the max and min bounds are proper
  REQUIRE(data.GetStandardDeviation() > 1000);
  REQUIRE(data.GetMax() > 100000);
  REQUIRE(data.GetMin() < 10);
}
