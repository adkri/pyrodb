#ifndef _pyrodb_bloom_filter
#define _pyrodb_bloom_filter

#include <bitset>
#include <string>

namespace pyrodb {

constexpr int BLOOM_SIZE = 65536;  // 2^16
class BloomFilter {
 public:
  BloomFilter() {}
  auto set(std::string key) -> void;
  auto test(std::string key) -> bool;

  uint32_t hash1(std::string key);
  uint32_t hash2(std::string key);
  uint32_t hash3(std::string key);

 private:
  std::bitset<BLOOM_SIZE> bloomset;
};
}  // namespace pyrodb

#endif
