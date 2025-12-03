#include "CanvasWindow.hpp"
#include<imgui.h>
#include<SDL2/SDL_opengl.h>

static GLuint canvasTexture = 0;
static float zoom = 20.0f;
static bool initialized = false;

static void UploadCanvasToTexture(const Canvas &canvas) {
  if (!initialized) {
    glGenTextures(1, &canvasTexture);
    initialized = true;
  }
  glBindTexture(GL_TEXTURE_2D, canvasTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, canvas.getWidth(), canvas.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, canvas.getPixels().data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void DrawCanvasWindow(Canvas &canvas) {
  ImGui::Begin("Canvas");

  UploadCanvasToTexture(canvas);

  ImVec2 size(canvas.getWidth() * zoom, canvas.getHeight() * zoom);

  ImDrawList *drawList = ImGui::GetWindowDrawList();
  ImVec2 p0 = ImGui::GetCursorScreenPos();
  const float checker = 10.0f;

  for(float y = 0; y < size.y; y += checker) {
    for(float x = 0; x < size.x; x += checker) {
      bool dark = (int(x / checker) + int(y / checker)) % 2;
      ImU32 col = dark ? IM_COL32(30, 30, 30, 255) : IM_COL32(60, 60, 60, 255);
      drawList->AddRectFilled(
        ImVec2(p0.x + x, p0.y + y),
        ImVec2(p0.x + x + checker, p0.y + y + checker),
        col
      );
    }
  }
  ImGui::Image(
    (void*)(uintptr_t)canvasTexture,
    size,
    ImVec2(0, 0),
    ImVec2(1, 1)
  );
  ImGui::End();
}
