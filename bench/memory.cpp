#include <benchmark/benchmark.h>

#include <map>
#include <set>
#include <string>
#include <vector>

namespace pyrodb {

constexpr int kInserts = 200000;

static void benchStdMap(benchmark::State& state) {
  while (state.KeepRunning()) {
    std::map<std::string, std::string> items;
    for (int i = 0; i < kInserts; i++) {
      std::string key("key" + std::to_string(i));
      std::string value("value" + std::to_string(i));

      items[key] = value;
    }
  }
}

static void benchStdVec(benchmark::State& state) {
  while (state.KeepRunning()) {
    struct Item {
      std::string key;
      std::string value;
    };
    std::vector<Item> items;

    for (int i = 0; i < kInserts; i++) {
      std::string key("key" + std::to_string(i));
      std::string value("value" + std::to_string(i));
      items.push_back(Item{key, value});
    }
  }
}

static void benchStdVecSorted(benchmark::State& state) {
  while (state.KeepRunning()) {
    struct Item {
      std::string key;
      std::string value;
    };
    std::vector<Item> items;

    for (int i = 0; i < kInserts; i++) {
      std::string key("key" + std::to_string(i));
      std::string value("value" + std::to_string(i));
      items.push_back(Item{key, value});
    }
    auto comp = [](Item const& left, Item const& right) -> bool {
      return left.key.compare(right.key);
    };
    std::sort(items.begin(), items.end(), comp);
  }
}

static void benchStdSet(benchmark::State& state) {
  while (state.KeepRunning()) {
    struct Item {
      std::string key;
      std::string value;
    };
    struct ItemComp {
      bool operator()(const Item& left, const Item& right) const {
        return left.key.compare(right.key);
      }
    };

    std::set<Item, ItemComp> items;

    for (int i = 0; i < kInserts; i++) {
      std::string key("key" + std::to_string(i));
      std::string value("value" + std::to_string(i));
      items.insert(Item{key, value});
    }
    /* auto comp = [](Item const& left, Item const& right) -> bool { */
    /*   return left.key.compare(right.key); */
    /* }; */
    /* std::sort(items.begin(), items.end(), comp); */
  }
}

BENCHMARK(benchStdMap)->Unit(benchmark::kMillisecond);
BENCHMARK(benchStdVec)->Unit(benchmark::kMillisecond);
BENCHMARK(benchStdSet)->Unit(benchmark::kMillisecond);
BENCHMARK(benchStdVecSorted)->Unit(benchmark::kMillisecond);

}  // namespace pyrodb
