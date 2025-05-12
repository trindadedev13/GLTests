#ifndef BRUT_INPUT_HANDLER_HPP
#define BRUT_INPUT_HANDLER_HPP

#define BRUT_KEY_W 0
#define BRUT_KEY_A 1
#define BRUT_KEY_S 2
#define BRUT_KEY_D 3
#define BRUT_KEY_ESC 4
#define BRUT_KEY_SPC 5

#define BRUT_KEY_ACTION_PRESS 6
#define BRUT_KEY_ACTION_REPEAT 7
#define BRUT_KEY_ACTION_RELEASE 8

#include <functional>

namespace Brut {

class InputHandler {
 public:
  using KeyCallback = std::function<void(int key, int action)>;

  void setOnKeyCallback(KeyCallback callback);

  void onKey(int key, int action);

 private:
  KeyCallback onKeyCallback = nullptr;
};

}  // namespace Brut

#endif