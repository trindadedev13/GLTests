#ifndef BRUT_SHADER_HPP
#define BRUT_SHADER_HPP

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Brut {

class Shader {
 public:
  Shader(const std::string vertShaderFilePath,
         const std::string fragShaderFilePath);
  ~Shader();

  void bind() const;
  void unbind() const;

  void sendUniformData(const std::string& varName, const glm::mat4& data);

 private:
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
  std::string readProgramSource(const std::string filePath);
};

}  // namespace Brut

#endif