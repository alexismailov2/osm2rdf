// Copyright 2020, University of Freiburg
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>.

#include <benchmark/benchmark.h>

#include <numeric>

#include "osm2ttl/util/DirectedGraph.h"

static void DirectedGraph_findSuccessors_0(benchmark::State& state) {
  osm2ttl::util::DirectedGraph dg;
  std::vector<uint64_t> vertices(state.range(0));
  std::iota(std::begin(vertices), std::end(vertices), 0);
  for (size_t i = 0; i < vertices.size() - 1; ++i) {
    dg.addEdge(vertices[i], vertices[i + 1]);
  }
  for (auto _ : state) {
    dg.findSuccessors(0);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(DirectedGraph_findSuccessors_0)
->RangeMultiplier(2)->Range(1<<1, 1<<8)->Complexity();

static void DirectedGraph_findSuccessors_N(benchmark::State& state) {
  osm2ttl::util::DirectedGraph dg;
  std::vector<uint64_t> vertices(state.range(0));
  std::iota(std::begin(vertices), std::end(vertices), 0);
  for (size_t i = 0; i < vertices.size() - 1; ++i) {
    dg.addEdge(vertices[i], vertices[i + 1]);
  }
  for (auto _ : state) {
    dg.findSuccessors(vertices.size());
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(DirectedGraph_findSuccessors_N)
->RangeMultiplier(2)->Range(1<<1, 1<<8)->Complexity();

static void DirectedGraph_findSuccessorsFast_0(benchmark::State& state) {
  osm2ttl::util::DirectedGraph dg;
  std::vector<uint64_t> vertices(state.range(0));
  std::iota(std::begin(vertices), std::end(vertices), 0);
  for (size_t i = 0; i < vertices.size() - 1; ++i) {
    dg.addEdge(vertices[i], vertices[i + 1]);
  }
  dg.prepareFindSuccessorsFast();
  for (auto _ : state) {
    dg.findSuccessorsFast(0);
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(DirectedGraph_findSuccessorsFast_0)
->RangeMultiplier(2)->Range(1<<1, 1<<8)->Complexity();

static void DirectedGraph_findSuccessorsFast_N(benchmark::State& state) {
  osm2ttl::util::DirectedGraph dg;
  std::vector<uint64_t> vertices(state.range(0));
  std::iota(std::begin(vertices), std::end(vertices), 0);
  for (size_t i = 0; i < vertices.size() - 1; ++i) {
    dg.addEdge(vertices[i], vertices[i + 1]);
  }
  dg.prepareFindSuccessorsFast();
  for (auto _ : state) {
    dg.findSuccessorsFast(vertices.size());
  }
  state.SetComplexityN(state.range(0));
}
BENCHMARK(DirectedGraph_findSuccessorsFast_N)
->RangeMultiplier(2)->Range(1<<1, 1<<8)->Complexity();
