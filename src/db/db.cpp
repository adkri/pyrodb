#include "pyrodb/db/db.hpp"

#include <memory>
#include <utility>

#include "pyrodb/type/types.hpp"

namespace pyrodb {

Db::Db() {
  memtable_ = std::make_unique<Memtable>();
}

auto Db::Put(const std::string& key, const std::string& value) -> void {
  auto handle = std::make_shared<ItemHandle>(key, value);
  if (memtable_->Set(std::move(handle))) {
    return;
  }
  // memtable is full
  auto sstable = memtable_->ExtractSSTable();
  auto new_run = std::make_shared<Run>();
  new_run->Set(sstable);
  memtable_->Clear();
  memtable_->Set(std::move(handle));

  // push run down to levels
  // levels_.front().Add(std::move(new_run), levels_.front(), levels_);
}

auto Db::Get(std::string key) -> std::string {
  auto handle = memtable_->Get(key);
  if (handle != nullptr) {
    return std::string(handle->value()->data());
  }
  return {};
}
}  // namespace pyrodb
