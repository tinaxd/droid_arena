#include "engine.h"
#include "sprite.h"
#include "util.h"
#include "display.h"
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
      Vector2D(0.0, 0.0), Vector2D(0.0, 0.0), 0.0,
      da::sprite::InstructionSet{I::FL, I::FR});
  auto sprite = new Sprite(state);
  
  std::vector<const Sprite *> sprites{sprite};

  engine->add_sprite(state);
  
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    
    engine->next();
    //debug_engine_stdout_(*engine);
    display->redraw(sprites);
  }

  delete display;
  delete engine;
  
  SDL_Quit();

  return 0;
}
