#include <vector>

#include "pyrodb/run/run.hpp"

namespace pyrodb {
constexpr int MAX_RUNS = 10;

class Level {
  uint32_t num_;
  uint32_t num_runs;
  std::vector<std::shared_ptr<Run>> runs_;

 public:
  auto MergeLevel(std::vector<Level>::iterator current) -> void;
  auto Add(std::shared_ptr<Run> run, std::vector<Level>::iterator current,
           std::vector<Level>& levels) {
    auto next = current++;
    if (current->num_runs == MAX_RUNS) {
      if (next == levels.end()) {
        Level l;
        std::shared_ptr<Run> last_run = current->runs_.back();
        current->runs_.pop_back();
        l.runs_.push_back(last_run);
        levels.push_back(l);
      } else {
        // auto new_run = MergeRun(current->runs_.back(), next->runs_.front());
        // current->runs_.pop_back();
        // next->runs_.begin()->swap(new_run);
      }
    }
    current->runs_.push_back(std::move(run));
  }
};

}  // namespace pyrodb
