#include "Windows.hpp"

void DrawToolsWindow(ToolState &toolState) {
  if (ImGui::Begin("Tools")) {
    ImGui::Text("Tools");
  }

  auto IconButton = [&](GLuint tex, Tool tool, const char* label, bool inLine = false) {
    bool selected = (toolState.currentTool == tool);
    
    if (toolState.currentTool == tool) {
      ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.20f, 0.45f, 1.0f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.25f, 0.55f, 1.0f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.15f, 0.35f, 0.9f, 1.0f));
    } else {
      ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.25f, 0.25f, 0.25f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(0.20f, 0.20f, 0.20f, 1.0f));
    }

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));

    ImGui::PushID((int)tool);
    ImTextureRef ref((ImTextureID)(size_t)tex);
    if (ImGui::ImageButton(
      label,
      ref,
      ImVec2(32, 32),
      ImVec2(0, 0),
      ImVec2(1, 1),
      ImVec4(0.0f, 0.6f, 1.0f, 0.4f),
      ImVec4(1,1,1,1)
    )) {
      toolState.currentTool = tool;
    }
    ImGui::PopID();
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip("%s", label);
    }
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar(2);
    if (inLine) ImGui::SameLine();
  };

  IconButton(textBrush, Tool::Brush, "Brush Tool", true);
  IconButton(textEraser, Tool::Eraser, "Eraser Tool", false);
  IconButton(textEyedropper, Tool::Eyedropper, "Eyedropper Tool", true);
  IconButton(textLine, Tool::Line, "Line Tool", false);
  if (toolState.currentTool == Tool::Brush || toolState.currentTool == Tool::Eyedropper || toolState.currentTool == Tool::Line) {
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_DisplayRGB;
    ImGui::Separator();
    ImGui::Text("Color");
    ImGui::ColorEdit4("##colorpicker", (float*)&toolState.currentColor, flags);
  }
  if (toolState.currentTool == Tool::Brush || toolState.currentTool == Tool::Eraser || toolState.currentTool == Tool::Line) {
    ImGui::Separator();
    ImGui::Text("Brush Settings");
    static float brushSize = 1.0f;
    ImGui::SliderFloat("Size", &brushSize, 1.0f, 100.0f);
  }
  ImGui::End();
}
