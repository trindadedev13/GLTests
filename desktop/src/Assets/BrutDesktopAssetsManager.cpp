#include "Assets/BrutDesktopAssetsManager.hpp"

#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

namespace Brut {

namespace Desktop {

AssetsManager::AssetsManager(const std::string& root) : assetsRoot(root) {}

std::string AssetsManager::readTextFile(const std::string& path) {
  std::ifstream file(assetsRoot + "/" + path);
  if (!file.is_open())
    return "";

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  return content;
}

bool AssetsManager::fileExists(const std::string& path) {
  return fs::exists(assetsRoot + "/" + path);
}

std::vector<std::string> AssetsManager::listFiles(const std::string& path) {
  std::vector<std::string> files;
  fs::path fullPath = assetsRoot + "/" + path;

  if (!fs::exists(fullPath) || !fs::is_directory(fullPath))
    return files;

  for (const auto& entry : fs::directory_iterator(fullPath)) {
    files.push_back(entry.path().filename().string());
  }

  return files;
}

}  // namespace Desktop

}  // namespace Brut