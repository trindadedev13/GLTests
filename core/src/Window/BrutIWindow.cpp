#include "Window/BrutIWindow.hpp"

#include <string>
#include <utility>

namespace Brut {

IWindow::IWindow(int w, int h, std::string name)
    : width(w), height(h), windowName(std::move(name)) {}

}  // namespace Brut