#include <vector>

#include "pyrodb/storage/sstable.hpp"

namespace pyrodb {
class Run {
 public:
  auto Set(std::shared_ptr<SSTable> table) { table_ = std::move(table); }
  auto GetTable() -> std::shared_ptr<SSTable> { return table_; }

 private:
  std::shared_ptr<SSTable> table_;
};

static auto MergeRun(Run& left, Run& right) -> Run {
  return left;
}
// static auto MergeRun(Run& left, Run& right) -> Run {
//   // two runs have non overlapping keys
//   Run newrun;
//   auto new_table = std::make_shared<SSTable>();
//   std::vector<std::shared_ptr<ItemHandle>> items;
//   uint32_t total_bytes = 0;

//   auto left_it = left.GetTable()->begin();
//   auto right_it = right.GetTable()->begin();

//   auto left_end = left.GetTable()->end();
//   auto right_end = right.GetTable()->end();

//   while (left_it != left_end && right_it != right_end) {
//     auto left = *left_it;
//     auto right = *right_it;
//     int compare = left.first.compare(right.first);
//     if (compare == 0) {
//       // are equal
//       auto handle = std::make_shared<ItemHandle>(left.first, left.second);
//       total_bytes += handle->ksize() + handle->vsize();
//       items.push_back(std::move(handle));
//       left_it++;
//       right_it++;
//     } else if (compare < 0) {
//       // left is smaller
//       auto handle = std::make_shared<ItemHandle>(left.first, left.second);
//       total_bytes += handle->ksize() + handle->vsize();
//       items.push_back(std::move(handle));
//       left_it++;
//     } else {
//       // right is smaller
//       auto handle = std::make_shared<ItemHandle>(right.first, right.second);
//       total_bytes += handle->ksize() + handle->vsize();
//       items.push_back(std::move(handle));
//       right_it++;
//     }
//   }

//   while (left_it != left_end) {
//     auto left = *left_it;
//     auto handle = std::make_shared<ItemHandle>(left.first, left.second);
//     total_bytes += handle->ksize() + handle->vsize();
//     items.push_back(std::move(handle));
//     left_it++;
//   }

//   while (right_it != right_end) {
//     auto right = *right_it;
//     auto handle = std::make_shared<ItemHandle>(right.first, right.second);
//     total_bytes += handle->ksize() + handle->vsize();
//     items.push_back(std::move(handle));
//     right_it++;
//   }

//   new_table->SerializeData(items, total_bytes);
//   newrun.Set(std::move(new_table));
//   return newrun;
// }
}  // namespace pyrodb
