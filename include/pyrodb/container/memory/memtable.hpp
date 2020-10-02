#ifndef _pyrodb_memtable
#define _pyrodb_memtable

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "pyrodb/storage/sstable.hpp"
#include "pyrodb/type/types.hpp"

namespace pyrodb {

constexpr int MAX_SIZE = 2 * 1024 * 4;
class Memtable {
 public:
  Memtable();
  auto Set(std::shared_ptr<ItemHandle> handle) -> bool;
  auto Get(const std::string& key) -> std::shared_ptr<ItemHandle>;
  auto Clear() -> void;
  auto ExtractSSTable() -> std::shared_ptr<SSTable>;

 private:
  std::vector<std::shared_ptr<ItemHandle>> items_;
  int current_size_;
};
}  // namespace pyrodb

#endif
