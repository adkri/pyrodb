#include <cassert>
#include <fstream>
#include <string>
#include <vector>

namespace pyrodb {
static auto loadFile(std::string filename) -> std::vector<char> {
  std::ifstream data_stream(filename, std::ios::binary | std::ios::ate);
  // TODO: change to avoid throwing exception
  if (!data_stream) {
    throw std::runtime_error(filename + ": " + std::strerror(errno));
  }

  auto end = data_stream.tellg();
  data_stream.seekg(0, std::ios::beg);

  auto size = std::size_t(end - data_stream.tellg());
  if (size == 0) {
    return {};
  }

  std::vector<char> buffer(size);
  if (!data_stream.read(buffer.data(), size)) {
    throw std::runtime_error(filename + ": " + std::strerror(errno));
  }

  return buffer;
}

static auto writeFile(const std::string directory, const std::string filename,
                      const std::vector<char>& src) -> void {
  std::filesystem::create_directory(directory);
  std::string path_ = directory + filename;
  std::ofstream d_file(path_, std::ios::binary | std::ios::out);
  d_file.write(src.data(), src.size());
}

static auto charToUIntVector(std::vector<char>& src,
                             std::vector<uint32_t>& dest) -> void {
  assert(dest.size() == src.size() / 4);
  for (uint32_t i = 0; i < dest.size(); i++) {
    auto offset = i * 4;
    uint32_t val = *(reinterpret_cast<uint32_t*>(src.data() + offset));
    dest.at(i) = val;
  }
}

static auto createPathIfNotExists(std::string path) -> void {
  if (!std::filesystem::exists(path)) {
    std::filesystem::create_directory(path);
  }
}

static auto findLevels(std::vector<std::string>& paths) -> void {
  for (const auto& entry : std::filesystem::directory_iterator("./db/")) {
    if (entry.is_directory()) {
      auto dirpath = std::string(entry.path());
      if (dirpath.rfind("level", 0) == 0) {
        paths.push_back(dirpath);
      }
    }
  }
}

static auto findRunsInLevel(std::string levelPath,
                            std::vector<std::string>& paths) -> void {
  for (const auto& entry : std::filesystem::directory_iterator(levelPath)) {
    if (!entry.is_directory()) {
      auto dirpath = std::string(entry.path());
      if (dirpath.rfind("run", 0) == 0) {
        paths.push_back(dirpath);
      }
    }
  }
}
}  // namespace pyrodb
