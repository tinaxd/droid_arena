find_package (PkgConfig REQUIRED)

pkg_check_modules (SDL2 REQUIRED sdl2)

add_executable (droidarena engine.cpp sprite.cpp)
target_include_directories (droidarena PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries (droidarena ${SDL2_LIBRARIES})
