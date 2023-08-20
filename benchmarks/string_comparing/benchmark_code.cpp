#include <string.h>

// CLang 13.0, optimization = None

static void StringStrCmp(benchmark::State& state) {
  const char* value = "value";
  for (auto _ : state) {
    bool isEqual = strcmp(value, "value") == 0;
  }
}
BENCHMARK(StringStrCmp);

static void StringCmp(benchmark::State& state) {
  const char* value = "value";
  for (auto _ : state) {
    bool isEqual = std::string(value) == "value";
  }
}
BENCHMARK(StringCmp);
