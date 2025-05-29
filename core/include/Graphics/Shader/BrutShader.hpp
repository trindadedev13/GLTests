#ifndef BRUT_SHADER_HPP
#define BRUT_SHADER_HPP

#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Assets/BrutIAssetsManager.hpp"

namespace Brut {

class Shader {
 public:
  Shader(IAssetsManager* assetsManager,
         const std::string vertShaderFilePath,
         const std::string fragShaderFilePath);
  ~Shader();

  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  Shader(Shader&& other) noexcept
      : assetsManager(other.assetsManager),
        programID(other.programID),
        vertexShaderID(other.vertexShaderID),
        fragmentShaderID(other.fragmentShaderID),
        vertexShaderFilePath(std::move(other.vertexShaderFilePath)),
        fragmentShaderFilePath(std::move(other.fragmentShaderFilePath)),
        uniformLocations(std::move(other.uniformLocations)) {
    other.programID = 0;
    other.vertexShaderID = 0;
    other.fragmentShaderID = 0;
  }

  Shader& operator=(Shader&& other) noexcept {
    if (this != &other) {
      if (programID)
        glDeleteProgram(programID);
      if (vertexShaderID)
        glDeleteShader(vertexShaderID);
      if (fragmentShaderID)
        glDeleteShader(fragmentShaderID);

      assetsManager = other.assetsManager;
      programID = other.programID;
      vertexShaderID = other.vertexShaderID;
      fragmentShaderID = other.fragmentShaderID;
      vertexShaderFilePath = std::move(other.vertexShaderFilePath);
      fragmentShaderFilePath = std::move(other.fragmentShaderFilePath);
      uniformLocations = std::move(other.uniformLocations);

      other.programID = 0;
      other.vertexShaderID = 0;
      other.fragmentShaderID = 0;
    }
    return *this;
  }

  void bind() const;
  void unbind() const;

  void sendUniformData(const std::string& varName, const glm::mat4& data);

 private:
  IAssetsManager* assetsManager;
  unsigned int programID;
  unsigned int vertexShaderID;
  unsigned int fragmentShaderID;
  std::string vertexShaderFilePath;
  std::string fragmentShaderFilePath;
  std::unordered_map<std::string, int> uniformLocations;

  void createShaders();
  void compileShaders();
  void linkProgram();
  void checkCompileError(unsigned int shaderID, int shaderType);
  void checkLinkError(const unsigned int programID);

  int getUniformLocation(const std::string& varName);
  std::string readProgramSource(const std::string& filePath);
};

}  // namespace Brut

#endif
