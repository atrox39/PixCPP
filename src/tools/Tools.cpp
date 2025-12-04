#include "Tools.hpp"
#include<cmath>

static void DrawLine(Canvas &canvas, int x0, int y0, int x1, int y1, uint32_t color) {
  auto &pix = canvas.setPixels();
  int w = canvas.getWidth();
  int h = canvas.getHeight();

  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;
  while (true) {
    if (x0 >= 0 && x0 < w && y0 >= 0 && y0 < h) {
      pix[y0 * w + x0] = color;
    }
    if (x0 == x1 && y0 == y1) break;
    int e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void ApplyTool(Canvas &canvas, ToolState &toolState, int px, int py, bool leftDown, bool rightDown) {
  if (rightDown) {
    uint32_t col = canvas.getPixels()[py * canvas.getWidth() + px];
    uint8_t r = col & 0xFF;
    uint8_t g = (col >> 8) & 0xFF;
    uint8_t b = (col >> 16) & 0xFF;
    uint8_t a = (col >> 24) & 0xFF;
    toolState.currentColor = ImVec4(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
    return;
  }
  uint8_t r = (uint8_t)(toolState.currentColor.x * 255.0f);
  uint8_t g = (uint8_t)(toolState.currentColor.y * 255.0f);
  uint8_t b = (uint8_t)(toolState.currentColor.z * 255.0f);
  uint8_t a = (uint8_t)(toolState.currentColor.w * 255.0f);
  uint32_t color = (a<<24) | (b<<16) | (g<<8) | r;

  if (leftDown && toolState.currentTool == Tool::Brush) {
    if (!toolState.painting) {
      toolState.painting = true;
      toolState.lastX = px;
      toolState.lastY = py;
      DrawLine(canvas, px, py, px, py, color);
      return;
    }
    DrawLine(canvas, toolState.lastX, toolState.lastY, px, py, color);
    toolState.lastX = px;
    toolState.lastY = py;
    return;
  }

  if (!leftDown) {
    toolState.painting = false;
    toolState.lastX = toolState.lastY = -1;
  }
}
