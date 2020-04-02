#include "display.h"
#include "sprite.h"
#include <SDL2_gfxPrimitives.h>

namespace da {

DisplayError::DisplayError(const std::string &what_arg)
    : std::runtime_error(what_arg) {}
DisplayError::DisplayError(const char *what_arg)
    : std::runtime_error(what_arg) {}

Display::Display(int width, int height) {
  window = SDL_CreateWindow("droid_arena viewer", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height,
                            SDL_WINDOW_OPENGL); // SDL_WINDOW_ALLOW_HIGHDPI?
  if (!window)
    throw DisplayError("failed to initialize SDL display");

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer)
    throw DisplayError("failed to create SDL renderer");

  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
}

Display::~Display() {
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  SDL_DestroyWindow(window);
  window = nullptr;
}

void Display::redraw(const std::vector<const Sprite *> &sprites) {
  clear_draw();

  for (auto sprite : sprites) {
    const auto &pos = sprite->state()->pos();
    aacircleRGBA(renderer, pos.x, pos.y, 1, 100, 100, 0,
               220);
  }

  SDL_RenderPresent(renderer);
}

void Display::clear_draw() { SDL_RenderClear(renderer); }

} // namespace da
