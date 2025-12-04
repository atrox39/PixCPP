#include "CanvasWindow.hpp"
#include "CanvasRender.hpp"
#include "tools/Tools.hpp"
#include<algorithm>

static CanvasRenderState renderState;

void DrawCanvasWindow(Canvas &canvas, ToolState &toolState) {
  ImGui::Begin("Canvas");

  ImGuiIO& io = ImGui::GetIO();
  if (!io.WantCaptureKeyboard) {
    if (ImGui::IsKeyPressed(ImGuiKey_B)) toolState.currentTool = Tool::Brush;
    if (ImGui::IsKeyPressed(ImGuiKey_E)) toolState.currentTool = Tool::Eraser;
    if (ImGui::IsKeyPressed(ImGuiKey_I)) toolState.currentTool = Tool::Eyedropper;
  }

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

  int px = -1, py = -1;
  bool inside = mouse.x >= origin.x && mouse.x <= origin.x + canvasSize.x &&
    mouse.y >= origin.y && mouse.y <= origin.y + canvasSize.y;
  if (inside) {
    px = (int)((mouse.x - origin.x) / renderState.zoom);
    py = (int)((mouse.y - origin.y) / renderState.zoom);
    ApplyTool(canvas, toolState, px, py, ImGui::IsMouseDown(ImGuiMouseButton_Left), ImGui::IsMouseDown(ImGuiMouseButton_Right));
  }

  if (toolState.currentTool == Tool::Line && toolState.lineMode && px >= 0 && py >= 0) {
    ImDrawList *drawList = ImGui::GetWindowDrawList();

    ImVec2 p0(
      origin.x + toolState.lineStartX * renderState.zoom + renderState.zoom * 0.5f,
      origin.y + toolState.lineStartY * renderState.zoom + renderState.zoom * 0.5f
    );

    ImVec2 p1(
      origin.x + px * renderState.zoom + renderState.zoom * 0.5f,
      origin.y + py * renderState.zoom + renderState.zoom * 0.5f
    );
    
    ImU32 col = IM_COL32(
      (int)(toolState.currentColor.x * 255.0f),
      (int)(toolState.currentColor.y * 255.0f),
      (int)(toolState.currentColor.z * 255.0f),
      255
    );
    drawList->AddLine(p0, p1, col, 2.0f); // 2px thickness is enough
  }

  ImGui::End();
}
