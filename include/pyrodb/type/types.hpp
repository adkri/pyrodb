#pragma once
#include <string>
#include <vector>

namespace pyrodb {

class ItemHandle {
 public:
  ItemHandle(const std::string& key, const std::string& value) {
    key_.resize(key.size() + 1);
    std::copy(key.c_str(), key.c_str() + key.size() + 1, key_.data());
    value_.resize(value.size() + 1);
    std::copy(value.c_str(), value.c_str() + value.size() + 1, value_.data());
    ksize_ = key_.size();
    vsize_ = value_.size();
  }

  auto key() -> const std::vector<char>* { return &key_; }
  auto value() -> const std::vector<char>* { return &value_; }
  auto ksize() -> uint32_t { return ksize_; }
  auto vsize() -> uint32_t { return vsize_; }

 private:
  std::vector<char> key_;
  std::vector<char> value_;
  uint32_t ksize_;
  uint32_t vsize_;
};

struct FileHandle {
  std::string file_id;
  std::vector<char> data_buf;
  std::vector<uint32_t> offset_buf;
};

constexpr int KEY_SIZE = 128;
constexpr int VALUE_SIZE = 4 * 1024;

}  // namespace pyrodb
