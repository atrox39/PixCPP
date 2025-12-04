#include "CanvasWindow.hpp"
#include "CanvasRender.hpp"
#include "tools/Tools.hpp"
#include<algorithm>

static CanvasRenderState renderState;

static void PreviewLine(
  ImDrawList* draw,
  int x0, int y0,
  int x1, int y1,
  float zoom, ImVec2 origin,
  ImU32 col
) {
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;
  while (true) {
    ImVec2 p0(
      origin.x + x0 * zoom,
      origin.y + y0 * zoom
    );
    ImVec2 p1(
      p0.x + zoom,
      p0.y + zoom
    );
  
    draw->AddRectFilled(p0, p1, col);
    if (x0 == x1 && y0 == y1) break;

    int e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
  }
}

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
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImU32 col = ImGui::ColorConvertFloat4ToU32(toolState.currentColor);
    PreviewLine(
      drawList,
      toolState.lineStartX, toolState.lineStartY,
      px, py,
      renderState.zoom,
      origin,
      col
    );
  }

  ImGui::End();
}
