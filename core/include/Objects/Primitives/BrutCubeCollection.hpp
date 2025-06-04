#ifndef BRUT_CUBE_COLLECTION_HPP
#define BRUT_CUBE_COLLECTION_HPP

#include <vector>

#include <glm/glm.hpp>

#include "Buffer/BrutBuffer.hpp"
#include "Buffer/BrutVertexArrayBuffer.hpp"
#include "Graphics/BrutColor.hpp"
#include "Objects/Primitives/BrutObject.hpp"

namespace Brut {

class CubeCollection : public Object {
 public:
  CubeCollection(unsigned int cubeCount);
  ~CubeCollection();

  void draw() override;

  void setModels(const std::vector<glm::mat4>& models);
  void setColors(const std::vector<Color>& colors);

 private:
  ArrayBuffer modelVBO;
  unsigned int cubeCount;

  void initCubeCollection();
  void fillBuffers();
  void linkBuffers();
};

}  // namespace Brut

#endif