#include "engine.h"
#include "util.h"
#include <SDL.h>
#include <iostream>
#include <memory>

using namespace da;

void sdl_init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  sdl_init();

  Engine *engine = new Engine();

  using I = da::sprite::Instruction;
  auto s = std::make_shared<sprite::SMState>(
      Vector2D(0.0, 0.0), Vector2D(0.0, 0.0), 0.0,
      da::sprite::InstructionSet{I::FL, I::FR});

  engine->add_sprite(s);
  for (int i = 0; i < 200; i++) {
    engine->next();
    std::cout << i << " ";
    debug_engine_stdout_(*engine);
    SDL_Delay(10);
  }

  delete engine;

  return 0;
}
