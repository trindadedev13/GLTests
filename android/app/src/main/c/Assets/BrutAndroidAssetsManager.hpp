#ifndef BRUT_ANDROID_ASSETS_MANAGER_HPP
#define BRUT_ANDROID_ASSETS_MANAGER_HPP

#include <string>
#include <vector>

#include "Assets/BrutIAssetsManager.hpp"
#include "jni/brut_android_assets_manager_jni.h"

namespace Brut {

namespace Android {

class AssetsManager : public IAssetsManager {
 public:
  explicit AssetsManager(BrutAssetsManagerJNI* asmgr);

  std::string readTextFile(const std::string& path) override;

  std::vector<int8_t> readBinaryFile(const std::string& path) override;

  bool fileExists(const std::string& path) override;

  std::vector<std::string> listFiles(const std::string& path) override;

 private:
  BrutAssetsManagerJNI* asmgr;
};

}  // namespace Android

}  // namespace Brut

#endif
