/* Author Ricardo Fabbri rfabbri@iprj.uerj.br 2025 */
#include <benchmark/benchmark.h>
#include <sorted_merge_3way.h>
#include <vector>
#include <algorithm>
#include <random>

// Fills a vector with sorted random integers.
static void fill_sorted_list(std::vector<int>& list, int size) {
    list.resize(size);
    if (size == 0) return;
    // Seed with a fixed value for reproducibility
    static std::mt19937 gen(42);
    std::uniform_int_distribution<> distrib(0, 1000000);

    for (int i = 0; i < size; ++i)
        list[i] = distrib(gen);
    std::sort(list.begin(), list.end());
}

class sorted_merge_3way_fixture : public benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State& state) {
    int size = state.range(0);
    fill_sorted_list(list_a, size);
    fill_sorted_list(list_b, size);
    fill_sorted_list(list_c, size);
    list_abc.resize(3 * size);
  }

  std::vector<int> list_a;
  std::vector<int> list_b;
  std::vector<int> list_c;
  std::vector<int> list_abc;
};

BENCHMARK_DEFINE_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)(benchmark::State& state) {
  for (auto _ : state) {
    sorted_merge_3way(list_a.data(), list_a.size(),
                 list_b.data(), list_b.size(),
                 list_c.data(), list_c.size(),
                 list_abc.data());
  }
  state.SetItemsProcessed(state.iterations() * 3 * state.range(0));
}

BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(0);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(1);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(2);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(10);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(50);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(100);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(500);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(1000);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(10000);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(100000);
BENCHMARK_REGISTER_F(sorted_merge_3way_fixture, BM_sorted_merge_3way)->Arg(1000000);

BENCHMARK_MAIN();
