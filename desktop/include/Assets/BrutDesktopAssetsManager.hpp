#ifndef BRUT_DESKTOP_ASSETS_MANAGER
#define BRUT_DESKTOP_ASSETS_MANAGER

#include <string>
#include <vector>

#include "Assets/BrutIAssetsManager.hpp"

namespace Brut {

namespace Desktop {

class AssetsManager : public IAssetsManager {
 public:
  explicit AssetsManager(const std::string& root);

  std::string readTextFile(const std::string& path) override;

  std::vector<int8_t> readBinaryFile(const std::string& path) override;

  bool fileExists(const std::string& path) override;

  std::vector<std::string> listFiles(const std::string& path) override;

 private:
  std::string assetsRoot;
};
}  // namespace Desktop

}  // namespace Brut

#endif
