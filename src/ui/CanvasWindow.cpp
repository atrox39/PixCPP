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

  ImVec2 contentMin = ImGui::GetCursorScreenPos();
  ImVec2 contentSize = ImGui::GetContentRegionAvail();
  ImVec2 canvasSize(canvas.getWidth() * zoom, canvas.getHeight() * zoom);
  ImVec2 origin;
  origin.x = contentMin.x + (contentSize.x - canvasSize.x) * 0.5f;
  origin.y = contentMin.y + (contentSize.y - canvasSize.y) * 0.5f;

  const float checker = zoom;

  for(float y = 0; y < size.y; y += checker) {
    for(float x = 0; x < size.x; x += checker) {
      bool dark = (int(x / checker) + int(y / checker)) % 2;
      ImU32 col = dark ? IM_COL32(30, 30, 30, 255) : IM_COL32(60, 60, 60, 255);
      drawList->AddRectFilled(
        ImVec2(origin.x + x, origin.y + y),
        ImVec2(origin.x + x + checker, origin.y + y + checker),
        col
      );
    }
  }

  ImGuiIO &io = ImGui::GetIO();
  ImVec2 mousePos = io.MousePos;
  bool inside = mousePos.x >= origin.x && mousePos.x <= origin.x + size.x &&
                mousePos.y >= origin.y && mousePos.y <= origin.y + size.y;
  if (inside && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
    float localX = (mousePos.x - origin.x) / zoom;
    float localY = (mousePos.y - origin.y) / zoom;
    int px = (int) localX;
    int py = (int) localY;
    if (px >= 0 && px < canvas.getWidth() && py >= 0 && py < canvas.getHeight()) {
      auto &pixel = canvas.setPixels();
      uint32_t color = 0xFF0000FF; // Temp red color
      pixel[py * canvas.getWidth() + px] = color;
    }
  }

  drawList->AddImage(
    (void*)(uintptr_t)canvasTexture,
    ImVec2(origin.x, origin.y),
    ImVec2(origin.x + size.x, origin.y + size.y),
    ImVec2(0.0f, 0.0f),
    ImVec2(1.0f, 1.0f)
  );
  ImGui::End();
}
