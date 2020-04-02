find_package (PkgConfig REQUIRED)

pkg_check_modules (SDL2 REQUIRED sdl2)

add_executable (droidarena
  main.cpp
  engine.cpp
  sprite.cpp
  sprite_instruction.cpp
  util.cpp
  display.cpp
)
target_include_directories (droidarena PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries (droidarena ${SDL2_LIBRARIES} ${SDL2_LIBRARIES}_gfx)
