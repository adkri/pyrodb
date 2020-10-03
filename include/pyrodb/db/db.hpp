#include <vector>

#include "pyrodb/container/memory/memtable.hpp"
#include "pyrodb/level/level.hpp"

namespace pyrodb {

class Db {
 public:
  Db();
  auto Put(const std::string& key, const std::string& value) -> void;
  auto Get(std::string key) -> std::string;

 private:
  std::vector<Level> levels_;
  std::unique_ptr<Memtable> memtable_;
};
}  // namespace pyrodb
