#ifndef BRUT_INPUT_HANDLER_HPP
#define BRUT_INPUT_HANDLER_HPP

#define BRUT_KEY_ACTION_UNKNOWN -1
#define BRUT_KEY_ACTION_PRESS 0
#define BRUT_KEY_ACTION_REPEAT 1
#define BRUT_KEY_ACTION_RELEASE 2

#define BRUT_KEY_UNKNOWN -1
#define BRUT_KEY_W 3
#define BRUT_KEY_A 4
#define BRUT_KEY_S 5
#define BRUT_KEY_D 6
#define BRUT_KEY_ESCAPE 7
#define BRUT_KEY_SPACE 8
#define BRUT_KEY_LEFT_CTRL 9
#define BRUT_KEY_RIGHT_CTRL 10

#include <functional>

#include <glm/glm.hpp>

namespace Brut {

/** Class responsible to "callback" the inputs. **/
class InputHandler {
 public:
  /** the callbacks to the input */
  /** KeyCallback for keyboard */
  /** MouseCallback for mouse */
  using KeyCallback = std::function<void(int key, int action)>;
  using MouseCallback = std::function<void(const glm::vec2 position)>;

  void setOnKeyCallback(KeyCallback callback);
  void setOnMouseCallback(MouseCallback callback);

  /** The platform implementation should call
   * these methods for game inputs.
   */
  void onKey(int key, int action);
  void onMouse(const glm::vec2 position);

 private:
  KeyCallback onKeyCallback = nullptr;
  MouseCallback onMouseCallback = nullptr;
};

}  // namespace Brut

#endif