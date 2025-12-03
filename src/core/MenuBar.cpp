#include "MenuBar.hpp"
#include<imgui.h>

void DrawMenuBar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New")) {}
      if (ImGui::MenuItem("Open...")) {}
      if (ImGui::MenuItem("Save")) {}
      if (ImGui::MenuItem("Save As...")) {}
      ImGui::Separator();
      if (ImGui::MenuItem("Exit")) {}
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo")) {}
      if (ImGui::MenuItem("Redo")) {}
      ImGui::Separator();
      if (ImGui::MenuItem("Cut")) {}
      if (ImGui::MenuItem("Copy")) {}
      if (ImGui::MenuItem("Paste")) {}
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help")) {
      ImGui::MenuItem("About", nullptr, false, false);
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
