#include "Graphics/Shader/BrutShadersManager.hpp"

#include <iostream>
#include <optional>
#include <string>
#include <stdexcept>

#include <SDL3/SDL.h>

#include "Assets/BrutIAssetsManager.hpp"
#include "Graphics/Shader/BrutShader.hpp"

namespace Brut {

ShadersManager::ShadersManager(IAssetsManager* _assetsManager)
    : assetsManager(_assetsManager) {
#ifdef BRUT_ANDROID
  std::string shadersPath = "shaders/android";
#else
  std::string shadersPath = "shaders/desktop";
#endif
  std::vector<std::string> fileList = assetsManager->listFiles(shadersPath);
  for (const std::string& filename : fileList) {
    SDL_Log("%s", filename.c_str());
    std::string fullPath = shadersPath + "/" + filename;
    shaders[filename] = fullPath;
  }
}

ShadersManager::~ShadersManager() {}

std::optional<std::reference_wrapper<Shader>> ShadersManager::get(
    const std::string& shaderName) {
  auto it = loadedShaders.find(shaderName);
  if (it != loadedShaders.end()) {
    return it->second;
  }

  auto shaderPath = shaders.find(shaderName);
  if (shaderPath == shaders.end())
    return std::nullopt;

  auto [insertIt, inserted] = loadedShaders.emplace(
      std::piecewise_construct, std::forward_as_tuple(shaderName),
      std::forward_as_tuple(assetsManager, shaderPath->second + "/main.vert",
                            shaderPath->second + "/main.frag"));

  return insertIt->second;
}

}  // namespace Brut
