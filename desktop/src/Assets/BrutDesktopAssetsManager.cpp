#include "Assets/BrutDesktopAssetsManager.hpp"

#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

#include <SDL3/SDL.h>

namespace fs = std::filesystem;

namespace Brut {

namespace Desktop {

AssetsManager::AssetsManager(const std::string& root) : assetsRoot(root) {}

std::string AssetsManager::readTextFile(const std::string& path) {
  std::ifstream file(assetsRoot + "/" + path);
  if (!file.is_open()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open file %s\n",
                 path.c_str());
    return "";
  }

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  return content;
}

std::vector<int8_t> AssetsManager::readBinaryFile(const std::string& path) {
  std::ifstream file(path, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open file %s\n",
                 path.c_str());
    return {};
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<int8_t> buffer(size);
  if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to read file %s\n",
                 path.c_str());
    return {};
  }

  return buffer;
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