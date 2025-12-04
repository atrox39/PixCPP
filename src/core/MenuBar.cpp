#include "MenuBar.hpp"

static bool showAboutModal = false;

void ShowAboutModal() {
  if (ImGui::BeginPopupModal("About", &showAboutModal, ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("PixCPP\nA simple pixel art editor.\n\n");
    ImGui::Separator();
    ImGui::Text("Version: 1.0.0\n");
    ImGui::Text("Author: Atrox39\n");
    ImGui::Text("GitHub: https://github.com/atrox39/PixCPP\n");
    if (ImGui::Button("OK")) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::EndPopup();
  }
}

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
      if (ImGui::MenuItem("About")) {
        showAboutModal = true;
        ImGui::OpenPopup("About");
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
    if (showAboutModal) {
      ShowAboutModal();
    }
  }
}
