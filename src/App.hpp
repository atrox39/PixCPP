#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

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

  void processEvent();
  void render();
};
