#ifndef BRUT_SHADERS_MANAGER_HPP
#define BRUT_SHADERS_MANAGER_HPP

#include "Graphics/Shader/BrutShader.hpp"

namespace Brut {

class ShadersManager {
 public:
  ShadersManager(const std::string shadersPath);
  ~ShadersManager();

  Shader get(const std::string shaderName);

 private:
  std::unordered_map<std::string, std::string> shaders;
};

}  // namespace Brut

#endif