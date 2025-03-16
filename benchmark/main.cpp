#include <benchmark/benchmark.h>

#include "folly/dynamic.h"
#include "folly/json.h"
#include "rapidjson/document.h"
#include "simdjson.h"
using namespace rapidjson;

const char *json = R"(
{
    "hello": "world",
    "t": true ,
    "f": false,
    "n": null,
    "i": 123,
    "pi": 3.1416,
    "a": [1, 2, 3, 4]
}
)";

static void BM_rapidjson(benchmark::State &state) {
  // Perform setup here
  for (auto _ : state) {
    Document d;
    d.Parse(json);
  }
}

static void BM_folly_dynamic(benchmark::State &state) {
  // Perform setup here
  for (auto _ : state) {
    folly::dynamic d = folly::parseJson(json);
  }
}

static void BM_simdjosn(benchmark::State &state) {
  using namespace simdjson; // optional
  // Perform setup here
  for (auto _ : state) {
    simdjson::dom::parser parser;
    simdjson::dom::element doc = parser.parse(std::string(json));
  }
}

// Register the function as a benchmark
BENCHMARK(BM_rapidjson);
BENCHMARK(BM_folly_dynamic);
BENCHMARK(BM_simdjosn);

// Run the benchmark
BENCHMARK_MAIN();