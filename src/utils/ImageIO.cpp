#include "ImageIO.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include<stb/stb_image_write.h>

bool SaveCanvasAsPNG(const Canvas &canvas, const std::string &path) {
  int w = canvas.getWidth();
  int h = canvas.getHeight();
  const std::vector<uint32_t> &src = canvas.getPixels();
  std::vector<uint8_t> out;
  out.resize(w * h * 4);

  for(int i = 0; i < w * h; i++) {
    uint32_t px = src[i];
    uint8_t r = px & 0xFF;
    uint8_t g = (px >> 8) & 0xFF;
    uint8_t b = (px >> 16) & 0xFF;
    uint8_t a = (px >> 24) & 0xFF;

    out[i * 4 + 0] = r;
    out[i * 4 + 1] = g;
    out[i * 4 + 2] = b;
    out[i * 4 + 3] = a;
  }

  int ok = stbi_write_png(path.c_str(), w, h, 4, out.data(), w * 4);
  return ok != 0;
}
