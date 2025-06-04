#include "BrutAndroidAssetsManager.hpp"

#include <cstdlib>
#include <string>
#include <vector>

#include <SDL3/SDL.h>

#include "jni/brut_android_assets_manager_jni.h"

namespace Brut {

namespace Android {

AssetsManager::AssetsManager(BrutAssetsManagerJNI* _asmgr) : asmgr(_asmgr) {}

std::string AssetsManager::readTextFile(const std::string& path) {
  const char* contentC = BrutAssetsManagerJNI_ReadTextFile(path.c_str());
  if (contentC == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to read text file %s\n",
                 path.c_str());
    return "";
  }

  std::string content{contentC};
  free((void*)contentC);

  return content;
}

std::vector<int8_t> AssetsManager::readBinaryFile(const std::string& path) {
  Int8Array* bytes = BrutAssetsManagerJNI_ReadBinaryFile(path.c_str());
  if (bytes == nullptr || bytes->data == nullptr || bytes->size == 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to read binary file %s\n", path.c_str());
    return {};
  }
  return std::vector<int8_t>(bytes->data, bytes->data + bytes->size);
}

bool AssetsManager::fileExists(const std::string& path) {
  return BrutAssetsManagerJNI_FileExists(path.c_str());
}

std::vector<std::string> AssetsManager::listFiles(const std::string& path) {
  int fileCount = 0;
  char** cFilesArray = BrutAssetsManagerJNI_ListFiles(path.c_str(), &fileCount);

  if (cFilesArray == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Failed to list files or not found\n");
    return {};
  }

  SDL_Log("Files found! count: %d\n", fileCount);

  std::vector<std::string> files;
  for (int i = 0; i < fileCount; ++i) {
    files.emplace_back(cFilesArray[i]);
  }

  BrutAssetsManagerJNI_FreeFileList(cFilesArray, fileCount);
  return files;
}

}  // namespace Android

}  // namespace Brut