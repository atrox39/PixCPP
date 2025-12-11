#include "MenuBar.hpp"
#include<algorithm>
#include<nfd.h>
#include<ui/Canvas.hpp>
#include<tools/FileIO.hpp>
#include<utils/ImageIO.hpp>

FileData gFile;

static bool gShowNewCanvasPopup = false;
static bool gShowAboutPopup = false;

static int newWidth  = 32;
static int newHeight = 32;

void DrawNewCanvasModal(Canvas &canvas) {
  if (gShowNewCanvasPopup) {
    ImGui::OpenPopup("NewCanvasPopup");
  }
  if (ImGui::BeginPopupModal("NewCanvasPopup", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
  {
    ImGui::Text("Create New Canvas");
    ImGui::Separator();

    ImGui::InputInt("Width", &newWidth);
    ImGui::InputInt("Height", &newHeight);

    newWidth = std::clamp(newWidth, 1, 128);
    newHeight = std::clamp(newHeight, 1, 128);

    ImGui::Separator();

    if (ImGui::Button("Create", ImVec2(120, 0)))
    {
      canvas.resize(newWidth, newHeight);

      auto &pix = canvas.setPixels();
      std::fill(pix.begin(), pix.end(), 0x00000000);
      gShowNewCanvasPopup = false;
      ImGui::CloseCurrentPopup();
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel", ImVec2(120, 0)))
    {
      gShowNewCanvasPopup = false;
      ImGui::CloseCurrentPopup();
    }

    ImGui::EndPopup();
  }
}

void DrawAboutModal() {
  if (gShowAboutPopup) {
    ImGui::OpenPopup("AboutPopup");
  }
  if (ImGui::BeginPopupModal("AboutPopup", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("PixCPP\nA simple pixel art editor.\n\n");
    ImGui::Separator();
    ImGui::Text("Version: 1.0.0\n");
    ImGui::Text("Author: Atrox39\n");
    ImGui::Text("GitHub: https://github.com/atrox39/PixCPP\n");
    if (ImGui::Button("OK")) {
      gShowAboutPopup = false;
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::EndPopup();
  }
}

static bool SaveCanvasWithDialog(Canvas &canvas) {
  NFD_Init();
  nfdu8char_t *outPath;
  nfdu8filteritem_t filterItem[1] = { { "PNG Image", "png" } };
  nfdsavedialogu8args_t args = { filterItem, 1 };
  bool success = false;
  if (NFD_SaveDialogU8_With(&outPath, &args) == NFD_OKAY) {
    if (SaveCanvasAsPNG(canvas, outPath)) {
      gFile.path = outPath;
      gFile.dirty = false;
      success = true;
    }
    NFD_FreePathU8(outPath);
  }
  NFD_Quit();
  return success;
}

void DrawMenuBar(Canvas &canvas) {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New")) {
        gShowNewCanvasPopup = true;
      }
      if (ImGui::MenuItem("Open...")) {
        NFD_Init();
        nfdu8char_t *outPath;
        nfdu8filteritem_t filterItem[1] = { { "PNG Image", "png" } };
        nfdopendialogu8args_t args = { filterItem, 1 };
        if (NFD_OpenDialogU8_With(&outPath, &args) == NFD_OKAY) {
          if (LoadImageToCanvas(outPath, canvas)) {
            gFile.path = outPath;
            gFile.dirty = false;
          }
          NFD_FreePathU8(outPath);
        }
        NFD_Quit();
      }
      if (ImGui::MenuItem("Save", nullptr, false, true)) {
        if (gFile.path.empty()) {
          SaveCanvasWithDialog(canvas);
        } else {
          SaveCanvasAsPNG(canvas, gFile.path);
          gFile.dirty = false;
        }
      }
      if (ImGui::MenuItem("Save As...")) {
        SaveCanvasWithDialog(canvas);
      }
      ImGui::Separator();
      if (ImGui::MenuItem("Exit")) {
        exit(0);
      }
      ImGui::EndMenu();
    }
    /* Temporarily disabled edit menu
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo")) {}
      if (ImGui::MenuItem("Redo")) {}
      ImGui::Separator();
      if (ImGui::MenuItem("Cut")) {}
      if (ImGui::MenuItem("Copy")) {}
      if (ImGui::MenuItem("Paste")) {}
      ImGui::EndMenu();
    }
    */
    if (ImGui::BeginMenu("Help")) {
      if (ImGui::MenuItem("About")) {
        gShowAboutPopup = true;
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }

  DrawAboutModal();
  DrawNewCanvasModal(canvas);
}
