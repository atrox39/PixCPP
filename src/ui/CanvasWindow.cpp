#include "CanvasWindow.hpp"
#include "CanvasRender.hpp"
#include "tools/Tools.hpp"
#include<algorithm>

static CanvasRenderState renderState;
static ToolState toolState;

void DrawCanvasWindow(Canvas &canvas) {
  ImGui::Begin("Canvas");
  ImGui::ColorEdit4("Color", (float*)&toolState.currentColor);

  if (ImGui::IsWindowHovered()) {
    float wheel = ImGui::GetIO().MouseWheel;
    if (wheel != 0.0f) {
      renderState.zoom += wheel * 2.0f;
      renderState.zoom = std::clamp(renderState.zoom, 4.0f, 64.0f);
    }
  }

  ImVec2 contentMin = ImGui::GetCursorScreenPos();
  ImVec2 contentSize = ImGui::GetContentRegionAvail();
  ImVec2 canvasSize(canvas.getWidth() * renderState.zoom, canvas.getHeight() * renderState.zoom);
  ImVec2 origin (
    origin.x = contentMin.x + (contentSize.x - canvasSize.x) * 0.5f,
    origin.y = contentMin.y + (contentSize.y - canvasSize.y) * 0.5f
  );

  RenderCheckerboard(canvas, renderState, origin);
  RenderCanvas(canvas, renderState, origin);

  ImVec2 mouse = ImGui::GetIO().MousePos;

  bool inside = mouse.x >= origin.x && mouse.x <= origin.x + canvasSize.x &&
    mouse.y >= origin.y && mouse.y <= origin.y + canvasSize.y;
  if (inside) {
    int px = (int)((mouse.x - origin.x) / renderState.zoom);
    int py = (int)((mouse.y - origin.y) / renderState.zoom);
    ApplyTool(canvas, toolState, px, py, ImGui::IsMouseDown(ImGuiMouseButton_Left), ImGui::IsMouseDown(ImGuiMouseButton_Right));
  }
  ImGui::End();
}
