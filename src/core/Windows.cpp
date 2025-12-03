#include "Windows.hpp"

void DrawWindows() {
  if (ImGui::Begin("Inspector")) {
    ImGui::Text("This is the inspector window.");
  }
  ImGui::End();
}
