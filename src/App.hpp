#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>
#include<ui/Canvas.hpp>

class App {
public:
  App();
  ~App();

  bool init();
  void run();
private:
  SDL_Window* window = nullptr;
  SDL_GLContext gl_context = nullptr;
  bool running = true;

  Canvas canvas{16, 16};

  void AllocateConsole();
  void processEvent();
  void render();
};
