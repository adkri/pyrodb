#ifndef _pyrodb_sstable
#define _pyrodb_sstable

#include <map>
#include <utility>
#include <vector>

#include "pyrodb/type/types.hpp"

namespace pyrodb {

class SSTable {
 public:
  SSTable() {}

  auto SerializeData(std::vector<std::shared_ptr<ItemHandle>>& items,
                     int total_bytes) -> void;

  auto DeserializeData(std::vector<char>& data_src,
                       std::vector<uint32_t>& offset_src,
                       std::vector<std::shared_ptr<ItemHandle>>& items) -> void;

  auto Data() -> const std::vector<char>* { return &data_; }
  auto Index() -> const std::vector<uint32_t>* { return &index_; }

  class iterator : public std::iterator<std::input_iterator_tag,
                                        std::pair<std::string, std::string>> {
   private:
    const SSTable* st;
    int current = 0;

   public:
    iterator() {}
    iterator(const SSTable* st, bool end) {
      this->st = st;
      if (end) {
        current = st->index_.size();
      }
    }

    iterator(const iterator& it) {
      st = it.st;
      current = it.current;
    }

    iterator& operator++() {
      current++;
      return *this;
    }

    iterator operator++(int) {
      iterator copy(*this);
      operator++();
      return copy;
    }

    bool operator==(const iterator& rhs) {
      return st == rhs.st && current == rhs.current;
    }

    bool operator!=(const iterator& rhs) { return !(*this == rhs); }

    std::pair<std::string, std::string> operator*() {
      auto key_offset = st->index_.at(current);
      std::string key(st->data_.data() + key_offset);
      int value_offset = key_offset + key.size() + 1;
      std::string value(st->data_.data() + value_offset);
      return make_pair(key, value);
    }

    friend class SSTable;
  };

  iterator begin() const { return iterator(this, false); }

  iterator end() const { return iterator(this, true); }

 private:
  auto binary_search(std::string& key) -> std::string;
  std::vector<char> data_;
  std::vector<uint32_t> index_;
};

}  // namespace pyrodb

#endif
