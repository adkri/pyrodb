#include "pyrodb/container/memory/memtable.hpp"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>

#include "pyrodb/util/util.hpp"

namespace pyrodb {
Memtable::Memtable() : current_size_(0) {}

auto Memtable::Set(std::shared_ptr<ItemHandle> handle) -> bool {
  uint32_t item_size = handle->ksize() + handle->vsize();

  if (current_size_ + item_size >= MAX_SIZE) {
    return false;
  }
  current_size_ += item_size;
  items_.push_back(std::move(handle));
  return true;
}

auto Memtable::Clear() -> void {
  items_.clear();
  current_size_ = 0;
}

auto Memtable::Get(const std::string& key) -> std::shared_ptr<ItemHandle> {
  const char* query_ = key.c_str();

  auto itemComp = [query_](const std::shared_ptr<ItemHandle>& arg) {
    const char* arg_str = arg->key()->data();
    return strcmp(query_, arg_str) == 0;
  };

  auto item = std::find_if(items_.begin(), items_.end(), itemComp);
  if (item != items_.end()) {
    return *item;
  }
  return nullptr;
}

auto Memtable::ExtractSSTable() -> std::shared_ptr<SSTable> {
  struct {
    auto operator()(const std::shared_ptr<ItemHandle>& lhs,
                    const std::shared_ptr<ItemHandle>& rhs) -> bool {
      std::string left(lhs->key()->data());
      std::string right(rhs->key()->data());
      return left.compare(right) < 0;
    }
  } ItemComp;
  std::sort(items_.begin(), items_.end(), ItemComp);

  auto sstable = std::make_shared<SSTable>();
  sstable->SerializeData(items_, current_size_);
  return sstable;
}

}  // namespace pyrodb
