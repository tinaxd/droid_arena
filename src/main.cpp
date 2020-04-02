#include "display.h"
#include "engine.h"
#include "sprite.h"
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
  Display *display = new Display();

  using I = da::sprite::Instruction;
  auto state = std::make_shared<sprite::SMState>(
      Vector2D(500.0, 800.0), Vector2D(0.0, 0.0), M_PI,
      da::sprite::InstructionSet{I::FL, I::F, I::ShootGun});
  
  auto state2 = std::make_shared<sprite::SMState>(
      Vector2D(500.0, 100.0), Vector2D(0.0, 0.0), 0.0,
      da::sprite::InstructionSet{I::FL, I::F, I::ShootGun});

  engine->add_sprite(state);
  engine->add_sprite(state2);

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }

    engine->next();

    display->redraw(engine->sprites());
  }

  delete display;
  delete engine;

  SDL_Quit();

  return 0;
}
