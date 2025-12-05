#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>

#include "FileIO.hpp"
#include<iostream>

bool LoadImageToCanvas(const std::string &path, Canvas &canvas) {
  int w, h, channels;
  unsigned char *data = stbi_load(path.c_str(), &w, &h, &channels, 4);
  if (!data) {
    std::cerr << "Failed to load image: " << stbi_failure_reason() << std::endl;
    return false;
  }

  if (w <= 0 || h <= 0) {
    std::cerr << "Invalid image dimensions." << std::endl;
    stbi_image_free(data);
    return false;
  }

  if (w > 128 || h > 128) {
    std::cerr << "Image dimensions exceed maximum allowed size of 128x128." << std::endl;
    stbi_image_free(data);
    return false;
  }

  canvas.resize(w, h);
  auto &pixels = canvas.setPixels();

  for (int i = 0; i < w * h; ++i) {
    uint8_t r = data[i * 4 + 0];
    uint8_t g = data[i * 4 + 1];
    uint8_t b = data[i * 4 + 2];
    uint8_t a = data[i * 4 + 3];
    pixels[i] = (a << 24) | (b << 16) | (g << 8) | r;
  }
  stbi_image_free(data);
  return true;
}
