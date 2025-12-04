#include "CanvasRender.hpp"

static void Upload(Canvas &canvas, CanvasRenderState &renderState) {
  if (!renderState.initialized) {
    glGenTextures(1, &renderState.texture);
    renderState.initialized = true;
  }
  glBindTexture(GL_TEXTURE_2D, renderState.texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, canvas.getWidth(), canvas.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, canvas.getPixels().data());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void RenderCheckerboard(Canvas& canvas, CanvasRenderState& rs, ImVec2 origin) {
  ImDrawList* dl = ImGui::GetWindowDrawList();

  for (int y = 0; y < canvas.getHeight(); ++y) {
    for (int x = 0; x < canvas.getWidth(); ++x) {
      bool dark = ((x + y) & 1) == 0;
      ImU32 col = dark ? IM_COL32(30,30,30,255) : IM_COL32(60,60,60,255);
      ImVec2 p0(origin.x + x * rs.zoom, origin.y + y * rs.zoom);
      ImVec2 p1(p0.x + rs.zoom, p0.y + rs.zoom);

      dl->AddRectFilled(p0, p1, col);
    }
  }
}

void RenderCanvas(Canvas& canvas, CanvasRenderState& rs, ImVec2 origin) {
  Upload(canvas, rs);
  
  ImVec2 size(canvas.getWidth() * rs.zoom, canvas.getHeight() * rs.zoom);

  ImGui::GetWindowDrawList()->AddImage(
    (void*)(uintptr_t)rs.texture,
    origin,
    ImVec2(origin.x + size.x, origin.y + size.y),
    ImVec2(0,0),
    ImVec2(1,1)
  );
}
