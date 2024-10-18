#include <benchmark/benchmark.h>

#include "graph.h"
using namespace mg;

static void benchmark_insertions(benchmark::State& s)
{
    for(auto _ : s)
    {
        Graph g;
        static const auto ITERATION_COUNT = 10e5;
        for(int i = 0; i < ITERATION_COUNT; i++)
        {
            g.CreateVertex();
        }
    }
}
BENCHMARK(benchmark_insertions)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
