#ifndef BRUT_IASSETS_MANAGER
#define BRUT_IASSETS_MANAGER

#include <cstdint>
#include <string>
#include <vector>

namespace Brut {

class IAssetsManager {
 public:
  virtual ~IAssetsManager() = default;

  virtual std::string readTextFile(const std::string& path) = 0;

  virtual std::vector<int8_t> readBinaryFile(const std::string& path) = 0;

  virtual bool fileExists(const std::string& path) = 0;

  virtual std::vector<std::string> listFiles(const std::string& path) = 0;
};

}  // namespace Brut

#endif
