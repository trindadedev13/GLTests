#ifndef BRUT_SHADERS_MANAGER_HPP
#define BRUT_SHADERS_MANAGER_HPP

#include <functional>
#include <optional>

#include "Assets/BrutIAssetsManager.hpp"
#include "Graphics/Shader/BrutShader.hpp"

namespace Brut {

class ShadersManager {
 public:
  ShadersManager(IAssetsManager* assetsManager);
  ~ShadersManager();

  std::optional<std::reference_wrapper<Shader>> get(
      const std::string& shaderName);

 private:
  IAssetsManager* assetsManager;
  std::unordered_map<std::string, std::string> shaders;
  std::unordered_map<std::string, Shader> loadedShaders;
};

}  // namespace Brut

#endif
