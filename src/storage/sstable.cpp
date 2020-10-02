#include <algorithm>
#include <ctime>
#include <fstream>
#include <pyrodb/storage/sstable.hpp>

namespace pyrodb {

auto SSTable::SerializeData(std::vector<std::shared_ptr<ItemHandle>>& items,
                            int total_bytes) -> void {
  data_.resize(total_bytes);
  index_.resize(items.size());
  uint32_t data_index = 0;
  uint32_t offset_index = 0;
  for (const auto& item : items) {
    uint32_t key_index = data_index;
    uint32_t value_index = data_index + item->ksize();

    std::copy(item->key()->data(), item->key()->data() + item->ksize(),
              data_.data() + key_index);

    std::copy(item->value()->data(), item->value()->data() + item->vsize(),
              data_.data() + value_index);

    // save key offset to the index
    index_[offset_index++] = data_index;

    data_index += item->ksize() + item->vsize();
  }
}

auto SSTable::DeserializeData(std::vector<char>& data_src,
                              std::vector<uint32_t>& offset_src,
                              std::vector<std::shared_ptr<ItemHandle>>& items)
    -> void {}

auto SSTable::binary_search(std::string& key) -> std::string {
  using vec_st = std::vector<uint32_t>::size_type;
  vec_st left = 0;
  vec_st right = index_.size();
  while (left < right) {
    vec_st mid = left + (right - left) / 2;
    int koffset = index_[mid];
    std::string mid_key(data_.data() + koffset);
    int cmp = key.compare(mid_key);
    if (cmp == 0) {
      int voffset = koffset + mid_key.size() + 1;
      return std::string(data_.data() + voffset);
    }
    if (cmp < 0) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return {};
}

}  // namespace pyrodb
