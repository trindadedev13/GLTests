#include "Graphics/Shader/BrutShadersManager.hpp"

#include <iostream>
#include <filesystem>
#include <string>
#include <stdexcept>

#include "Graphics/Shader/BrutShader.hpp"

namespace fs = std::filesystem;

namespace Brut {

ShadersManager::ShadersManager(const std::string shadersPath) {
  for (const auto& entry : fs::directory_iterator(shadersPath)) {
    std::string shaderName = entry.path().string().substr(
        entry.path().string().find_last_of("/") + 1);
    std::string shaderPath = entry.path().string();
    shaders[shaderName] = shaderPath;
  }
};

ShadersManager::~ShadersManager() {}

Shader ShadersManager::get(const std::string shaderName) {
  if (shaders.find(shaderName) != shaders.end()) {
    return Shader(shaders[shaderName] + "/main.vert",
                  shaders[shaderName] + "/main.frag");
  }
  throw std::runtime_error("Shader not found: " + shaderName);
}

}  // namespace Brut