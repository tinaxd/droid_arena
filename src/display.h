#pragma once

#include "sprite.h"
#include <SDL.h>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include "util.h"

namespace da {

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

  template <
      class S,
      typename std::enable_if<
          std::is_base_of<Sprite, typename std::pointer_traits<S>::element_type>::value,
          int>::type = 0>
  void redraw(const std::vector<S> &sprites) {
    clear_draw();

    for (S sprite : sprites) {
      draw_sprite(deref(sprite).state()->pos(), deref(sprite).state()->radius());
    }

    update_draw();
  }
  
  template <
      class S,
      typename std::enable_if<
          std::is_base_of<sprite::State, typename std::pointer_traits<S>::element_type>::value,
          int>::type = 0>
  void redraw(const std::vector<S> &sprites) {
    clear_draw();

    for (S sprite : sprites) {
      draw_sprite(deref(sprite).pos(), deref(sprite).radius());
    }

    update_draw();
  }

private:
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  void clear_draw();
  void update_draw();

  void draw_sprite(const sprite::Position &pos, double radius);
};

} // namespace da
