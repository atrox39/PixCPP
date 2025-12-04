#pragma once
#include "ui/Canvas.hpp"
#include<imgui.h>

enum class Tool {
  Brush,
  Eyedropper,
  Line
};

struct ToolState {
  Tool currentTool = Tool::Brush;
  bool painting = false;
  int lastX = -1, lastY = -1;
  bool lineMode = false;
  int lineStartX = -1, lineStartY = -1;
  ImVec4 currentColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
};

void ApplyTool(Canvas &canvas, ToolState &toolState, int px, int py, bool leftDown, bool rightDown);
