#pragma once
#include "Canvas.hpp"
#include<imgui.h>
#include<SDL2/SDL_opengl.h>

struct CanvasRenderState {
  float zoom = 20.0f;
  GLuint texture = 0;
  bool initialized = false;
};

void RenderCanvas(Canvas &canvas, CanvasRenderState &renderState, ImVec2 origin);
void RenderCheckerboard(Canvas &canvas, CanvasRenderState &renderState, ImVec2 origin);
