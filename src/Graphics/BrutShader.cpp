#include "Graphics/BrutShader.hpp"
#include "Error/BrutError.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Brut {
Shader::Shader(const std::string vertShaderFilePath,
               const std::string fragShaderFilePath)
    : programID(0),
      vertexShaderID(0),
      fragmentShaderID(0),
      vertexShaderFilePath(vertShaderFilePath),
      fragmentShaderFilePath(fragShaderFilePath) {
  createShaders();
}

Shader::~Shader() {
  glDeleteProgram(programID);
}

void Shader::bind() const {
  glUseProgram(programID);
}

void Shader::unbind() const {
  glUseProgram(0);
}

void Shader::sendUniformData(const std::string& varName,
                             const glm::mat4& data) {
  int id = getUniformLocation(varName);
  glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(data));
}

void Shader::createShaders() {
  programID = glCreateProgram();
  if (programID == 0) {
    fatalError("Error creating Program Object.");
  }

  vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
  if (vertexShaderID == 0) {
    fatalError("Error creating Vertex Shader object.");
  }

  fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
  if (fragmentShaderID == 0) {
    fatalError("Error creating Fragment Shader object.");
  }

  compileShaders();
  linkProgram();
}

void Shader::compileShaders() {
  std::string vsCode, fsCode;
  vsCode = readProgramSource(vertexShaderFilePath);
  fsCode = readProgramSource(fragmentShaderFilePath);

  const char* vsFinalCode = vsCode.c_str();
  const char* fsFinalCode = fsCode.c_str();

  glShaderSource(vertexShaderID, 1, &vsFinalCode, NULL);
  glShaderSource(fragmentShaderID, 1, &fsFinalCode, NULL);

  glCompileShader(vertexShaderID);
  checkCompileError(vertexShaderID, GL_VERTEX_SHADER);

  glCompileShader(fragmentShaderID);
  checkCompileError(fragmentShaderID, GL_FRAGMENT_SHADER);
}

void Shader::linkProgram() {
  glAttachShader(programID, vertexShaderID);
  glAttachShader(programID, fragmentShaderID);
  {
    glLinkProgram(programID);
    checkLinkError(programID);
  }
  glDetachShader(programID, vertexShaderID);
  glDetachShader(programID, fragmentShaderID);

  glDeleteShader(vertexShaderID);
  glDeleteShader(fragmentShaderID);
}

int Shader::getUniformLocation(const std::string& variableName) {
  if (uniformLocations.find(variableName) != uniformLocations.end()) {
    return uniformLocations[variableName];
  }

  int id = glGetUniformLocation(programID, variableName.c_str());
  if (id == -1) {
    fatalError("Uniform " + variableName + " not Found.");
  }
  uniformLocations[variableName] = id;

  return id;
}

std::string Shader::readProgramSource(const std::string filePath) {
  std::fstream file(filePath);

  std::stringstream ss;
  std::string line;

  while (getline(file, line)) {
    ss << line << "\n";
  }
  file.close();

  return ss.str();
}

void Shader::checkCompileError(unsigned int shaderID, int shaderType) {
  int compileStatus;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus == GL_FALSE) {
    int infoLogLength;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

    char* message = new char[infoLogLength];

    glGetShaderInfoLog(shaderID, infoLogLength, NULL, message);
    std::string shaderName =
        (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment");

    std::cout << message << std::endl;
    delete[] message;

    fatalError("Compilation failed in " + shaderName + " Shader");

  } else {
    std::string shaderName =
        (shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment");
    std::cout << "Shader compilation successful in " + shaderName + " Shader"
              << std::endl;
  }
}

void Shader::checkLinkError(const unsigned int programId) {
  int linkStatus;
  glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
  if (linkStatus == GL_FALSE) {
    int infoLogLength;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

    char* message = new char[infoLogLength];

    glGetProgramInfoLog(programId, infoLogLength, NULL, message);
    std::cout << message << std::endl;
    fatalError("Shaders failed to link!!!");

    glDeleteProgram(programId);

    delete[] message;

  } else {
    std::cout << "Shader link was successful! \n";
  }
}
}  // namespace Brut