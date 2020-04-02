#pragma once

#include <SDL.h>
#include <stdexcept>
#include <vector>

namespace da {

class Sprite;
class DisplayError;
class Display;

class DisplayError : public std::runtime_error {
public:
  explicit DisplayError(const std::string &what_arg);
  explicit DisplayError(const char *what_arg);
};

/// Game preview viewer.
///
/// Draw sprites using both texture and state data of each sprite.
/// Assuming SDL_Init is already called.
class Display {
public:
  Display(int width = 1000, int height = 1000);
  ~Display();
  
  void redraw(const std::vector<const Sprite *>& sprites);

private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  
  void clear_draw();
};

} // namespace da
