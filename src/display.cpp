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
  if (window == nullptr) {
    throw DisplayError("failed to initialize SDL display");
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    throw DisplayError("failed to create SDL renderer");
  }

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
    const auto radius = sprite->state()->radius();
    SDL_FRect rect;
    rect.x = pos.x - radius;
    rect.y = pos.y - radius;
    rect.w = 2 * radius;
    rect.h = 2 * radius;
    SDL_SetRenderDrawColor(renderer, 100, 100, 0, 200);
    SDL_RenderFillRectF(renderer, &rect);
    
    // TODO: draw a marker so that we can know in which direction a sprte is standing.
  }

  SDL_RenderPresent(renderer);
}

void Display::clear_draw() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);
}

} // namespace da
