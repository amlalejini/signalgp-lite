#include <benchmark/benchmark.h>

#include "sgpl/algorithm/execute_cpu.hpp"
#include "sgpl/config/Spec.hpp"
#include "sgpl/library/prefab/CompleteOpLibrary.hpp"

using spec_t = sgpl::Spec<sgpl::CompleteOpLibrary>;

static void Lite_Complete(benchmark::State& state) {

  emp::Random rand;

  sgpl::Cpu<spec_t> cpu;
  sgpl::Program<spec_t> program{ rand, 100 };
  cpu.InitializeAnchors( program );

  // Perform setup here
  for (auto _ : state) {

    while ( cpu.GetNumFreeCores() ) {
      cpu.LaunchCore( emp::BitSet<32>(rand) );
    }

    // This code gets timed
    // ( with this setup, sgp-lite potentially has 16x more iterations )
    for (size_t i = 0; i < 16; ++i)
      sgpl::execute_cpu<spec_t>( 1, cpu, program );
  }

  assert( cpu.GetNumCores() );

}
// Register the function as a benchmark
BENCHMARK(Lite_Complete);
// Run the benchmark
BENCHMARK_MAIN();
